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
struct rdac_dh_data {int /*<<< orphan*/  state; TYPE_1__* ctlr; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; scalar_t__ array_name; } ;

/* Variables and functions */
 int ADD_TO_MLQUEUE ; 
#define  ILLEGAL_REQUEST 130 
#define  NOT_READY 129 
 int /*<<< orphan*/  RDAC_LOG (int /*<<< orphan*/ ,struct scsi_device*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RDAC_LOG_SENSE ; 
 int /*<<< orphan*/  RDAC_STATE_PASSIVE ; 
 int SCSI_RETURN_NOT_HANDLED ; 
 int SUCCESS ; 
#define  UNIT_ATTENTION 128 

__attribute__((used)) static int rdac_check_sense(struct scsi_device *sdev,
				struct scsi_sense_hdr *sense_hdr)
{
	struct rdac_dh_data *h = sdev->handler_data;

	RDAC_LOG(RDAC_LOG_SENSE, sdev, "array %s, ctlr %d, "
			"I/O returned with sense %02x/%02x/%02x",
			(char *) h->ctlr->array_name, h->ctlr->index,
			sense_hdr->sense_key, sense_hdr->asc, sense_hdr->ascq);

	switch (sense_hdr->sense_key) {
	case NOT_READY:
		if (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x01)
			/* LUN Not Ready - Logical Unit Not Ready and is in
			* the process of becoming ready
			* Just retry.
			*/
			return ADD_TO_MLQUEUE;
		if (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x81)
			/* LUN Not Ready - Storage firmware incompatible
			 * Manual code synchonisation required.
			 *
			 * Nothing we can do here. Try to bypass the path.
			 */
			return SUCCESS;
		if (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0xA1)
			/* LUN Not Ready - Quiescense in progress
			 *
			 * Just retry and wait.
			 */
			return ADD_TO_MLQUEUE;
		if (sense_hdr->asc == 0xA1  && sense_hdr->ascq == 0x02)
			/* LUN Not Ready - Quiescense in progress
			 * or has been achieved
			 * Just retry.
			 */
			return ADD_TO_MLQUEUE;
		break;
	case ILLEGAL_REQUEST:
		if (sense_hdr->asc == 0x94 && sense_hdr->ascq == 0x01) {
			/* Invalid Request - Current Logical Unit Ownership.
			 * Controller is not the current owner of the LUN,
			 * Fail the path, so that the other path be used.
			 */
			h->state = RDAC_STATE_PASSIVE;
			return SUCCESS;
		}
		break;
	case UNIT_ATTENTION:
		if (sense_hdr->asc == 0x29 && sense_hdr->ascq == 0x00)
			/*
			 * Power On, Reset, or Bus Device Reset, just retry.
			 */
			return ADD_TO_MLQUEUE;
		if (sense_hdr->asc == 0x8b && sense_hdr->ascq == 0x02)
			/*
			 * Quiescence in progress , just retry.
			 */
			return ADD_TO_MLQUEUE;
		break;
	}
	/* success just means we do not care what scsi-ml does */
	return SCSI_RETURN_NOT_HANDLED;
}