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
struct scsi_sense_hdr {int asc; int ascq; int /*<<< orphan*/  sense_key; } ;
struct scsi_device {struct rdac_dh_data* handler_data; } ;
struct rdac_dh_data {TYPE_1__* ctlr; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; scalar_t__ array_name; } ;

/* Variables and functions */
#define  ABORTED_COMMAND 132 
#define  ILLEGAL_REQUEST 131 
#define  NOT_READY 130 
#define  NO_SENSE 129 
 int /*<<< orphan*/  RDAC_LOG (int /*<<< orphan*/ ,struct scsi_device*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RDAC_LOG_FAILOVER ; 
 int SCSI_DH_IMM_RETRY ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_RETRY ; 
#define  UNIT_ATTENTION 128 
 int /*<<< orphan*/  scsi_sense_valid (struct scsi_sense_hdr*) ; 

__attribute__((used)) static int mode_select_handle_sense(struct scsi_device *sdev,
				    struct scsi_sense_hdr *sense_hdr)
{
	int err = SCSI_DH_IO;
	struct rdac_dh_data *h = sdev->handler_data;

	if (!scsi_sense_valid(sense_hdr))
		goto done;

	switch (sense_hdr->sense_key) {
	case NO_SENSE:
	case ABORTED_COMMAND:
	case UNIT_ATTENTION:
		err = SCSI_DH_RETRY;
		break;
	case NOT_READY:
		if (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x01)
			/* LUN Not Ready and is in the Process of Becoming
			 * Ready
			 */
			err = SCSI_DH_RETRY;
		break;
	case ILLEGAL_REQUEST:
		if (sense_hdr->asc == 0x91 && sense_hdr->ascq == 0x36)
			/*
			 * Command Lock contention
			 */
			err = SCSI_DH_IMM_RETRY;
		break;
	default:
		break;
	}

	RDAC_LOG(RDAC_LOG_FAILOVER, sdev, "array %s, ctlr %d, "
		"MODE_SELECT returned with sense %02x/%02x/%02x",
		(char *) h->ctlr->array_name, h->ctlr->index,
		sense_hdr->sense_key, sense_hdr->asc, sense_hdr->ascq);

done:
	return err;
}