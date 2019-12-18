#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ctlr_info {int dummy; } ;
struct CommandList {TYPE_1__* err_info; } ;
struct TYPE_2__ {unsigned char* SenseInfo; int SenseLen; int /*<<< orphan*/  ScsiStatus; int /*<<< orphan*/  CommandStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCQ_LUN_NOT_READY_FORMAT_IN_PROGRESS ; 
 int /*<<< orphan*/  ASCQ_LUN_NOT_READY_INITIALIZING_CMD_REQ ; 
 int /*<<< orphan*/  DEFAULT_REPLY_QUEUE ; 
#define  HPSA_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER 138 
#define  HPSA_LV_ENCRYPTED_NO_KEY 137 
#define  HPSA_LV_FAILED 136 
#define  HPSA_LV_NOT_AVAILABLE 135 
 unsigned char HPSA_LV_OK ; 
#define  HPSA_LV_PENDING_RPI 134 
#define  HPSA_LV_PLAINTEXT_IN_ENCRYPT_ONLY_CONTROLLER 133 
#define  HPSA_LV_UNDERGOING_ENCRYPTION 132 
#define  HPSA_LV_UNDERGOING_ENCRYPTION_REKEYING 131 
#define  HPSA_LV_UNDERGOING_ERASE 130 
#define  HPSA_LV_UNDERGOING_RPI 129 
#define  HPSA_VPD_LV_STATUS_UNSUPPORTED 128 
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int /*<<< orphan*/  TEST_UNIT_READY ; 
 int /*<<< orphan*/  TYPE_CMD ; 
 struct CommandList* cmd_alloc (struct ctlr_info*) ; 
 int /*<<< orphan*/  cmd_free (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  decode_sense_data (unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_cmd (struct CommandList*,int /*<<< orphan*/ ,struct ctlr_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int hpsa_get_volume_status (struct ctlr_info*,unsigned char*) ; 
 int hpsa_scsi_do_simple_cmd (struct ctlr_info*,struct CommandList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char hpsa_volume_offline(struct ctlr_info *h,
					unsigned char scsi3addr[])
{
	struct CommandList *c;
	unsigned char *sense;
	u8 sense_key, asc, ascq;
	int sense_len;
	int rc, ldstat = 0;
	u16 cmd_status;
	u8 scsi_status;
#define ASC_LUN_NOT_READY 0x04
#define ASCQ_LUN_NOT_READY_FORMAT_IN_PROGRESS 0x04
#define ASCQ_LUN_NOT_READY_INITIALIZING_CMD_REQ 0x02

	c = cmd_alloc(h);

	(void) fill_cmd(c, TEST_UNIT_READY, h, NULL, 0, 0, scsi3addr, TYPE_CMD);
	rc = hpsa_scsi_do_simple_cmd(h, c, DEFAULT_REPLY_QUEUE,
					NO_TIMEOUT);
	if (rc) {
		cmd_free(h, c);
		return HPSA_VPD_LV_STATUS_UNSUPPORTED;
	}
	sense = c->err_info->SenseInfo;
	if (c->err_info->SenseLen > sizeof(c->err_info->SenseInfo))
		sense_len = sizeof(c->err_info->SenseInfo);
	else
		sense_len = c->err_info->SenseLen;
	decode_sense_data(sense, sense_len, &sense_key, &asc, &ascq);
	cmd_status = c->err_info->CommandStatus;
	scsi_status = c->err_info->ScsiStatus;
	cmd_free(h, c);

	/* Determine the reason for not ready state */
	ldstat = hpsa_get_volume_status(h, scsi3addr);

	/* Keep volume offline in certain cases: */
	switch (ldstat) {
	case HPSA_LV_FAILED:
	case HPSA_LV_UNDERGOING_ERASE:
	case HPSA_LV_NOT_AVAILABLE:
	case HPSA_LV_UNDERGOING_RPI:
	case HPSA_LV_PENDING_RPI:
	case HPSA_LV_ENCRYPTED_NO_KEY:
	case HPSA_LV_PLAINTEXT_IN_ENCRYPT_ONLY_CONTROLLER:
	case HPSA_LV_UNDERGOING_ENCRYPTION:
	case HPSA_LV_UNDERGOING_ENCRYPTION_REKEYING:
	case HPSA_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER:
		return ldstat;
	case HPSA_VPD_LV_STATUS_UNSUPPORTED:
		/* If VPD status page isn't available,
		 * use ASC/ASCQ to determine state
		 */
		if ((ascq == ASCQ_LUN_NOT_READY_FORMAT_IN_PROGRESS) ||
			(ascq == ASCQ_LUN_NOT_READY_INITIALIZING_CMD_REQ))
			return ldstat;
		break;
	default:
		break;
	}
	return HPSA_LV_OK;
}