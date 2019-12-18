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
typedef  int u16 ;
struct ctlr_info {int dummy; } ;
struct bmic_identify_physical_device {int dummy; } ;
struct ErrorInfo {scalar_t__ CommandStatus; } ;
struct TYPE_2__ {int* CDB; } ;
struct CommandList {struct ErrorInfo* err_info; TYPE_1__ Request; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMIC_IDENTIFY_PHYSICAL_DEVICE ; 
 scalar_t__ CMD_DATA_UNDERRUN ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int IO_OK ; 
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int /*<<< orphan*/  RAID_CTLR_LUNID ; 
 int /*<<< orphan*/  TYPE_CMD ; 
 struct CommandList* cmd_alloc (struct ctlr_info*) ; 
 int /*<<< orphan*/  cmd_free (struct ctlr_info*,struct CommandList*) ; 
 int fill_cmd (struct CommandList*,int /*<<< orphan*/ ,struct ctlr_info*,struct bmic_identify_physical_device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_scsi_do_simple_cmd_with_retry (struct ctlr_info*,struct CommandList*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_scsi_interpret_error (struct ctlr_info*,struct CommandList*) ; 

__attribute__((used)) static int hpsa_bmic_id_physical_device(struct ctlr_info *h,
		unsigned char scsi3addr[], u16 bmic_device_index,
		struct bmic_identify_physical_device *buf, size_t bufsize)
{
	int rc = IO_OK;
	struct CommandList *c;
	struct ErrorInfo *ei;

	c = cmd_alloc(h);
	rc = fill_cmd(c, BMIC_IDENTIFY_PHYSICAL_DEVICE, h, buf, bufsize,
		0, RAID_CTLR_LUNID, TYPE_CMD);
	if (rc)
		goto out;

	c->Request.CDB[2] = bmic_device_index & 0xff;
	c->Request.CDB[9] = (bmic_device_index >> 8) & 0xff;

	hpsa_scsi_do_simple_cmd_with_retry(h, c, DMA_FROM_DEVICE,
						NO_TIMEOUT);
	ei = c->err_info;
	if (ei->CommandStatus != 0 && ei->CommandStatus != CMD_DATA_UNDERRUN) {
		hpsa_scsi_interpret_error(h, c);
		rc = -1;
	}
out:
	cmd_free(h, c);

	return rc;
}