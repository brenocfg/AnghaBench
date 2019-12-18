#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_sense_hdr {int sense_key; int asc; int ascq; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int ADD_TO_MLQUEUE ; 
#define  ILLEGAL_REQUEST 130 
#define  NOT_READY 129 
 int SCSI_RETURN_NOT_HANDLED ; 
 int SUCCESS ; 
#define  UNIT_ATTENTION 128 

__attribute__((used)) static int clariion_check_sense(struct scsi_device *sdev,
				struct scsi_sense_hdr *sense_hdr)
{
	switch (sense_hdr->sense_key) {
	case NOT_READY:
		if (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x03)
			/*
			 * LUN Not Ready - Manual Intervention Required
			 * indicates this is a passive path.
			 *
			 * FIXME: However, if this is seen and EVPD C0
			 * indicates that this is due to a NDU in
			 * progress, we should set FAIL_PATH too.
			 * This indicates we might have to do a SCSI
			 * inquiry in the end_io path. Ugh.
			 *
			 * Can return FAILED only when we want the error
			 * recovery process to kick in.
			 */
			return SUCCESS;
		break;
	case ILLEGAL_REQUEST:
		if (sense_hdr->asc == 0x25 && sense_hdr->ascq == 0x01)
			/*
			 * An array based copy is in progress. Do not
			 * fail the path, do not bypass to another PG,
			 * do not retry. Fail the IO immediately.
			 * (Actually this is the same conclusion as in
			 * the default handler, but lets make sure.)
			 *
			 * Can return FAILED only when we want the error
			 * recovery process to kick in.
			 */
			return SUCCESS;
		break;
	case UNIT_ATTENTION:
		if (sense_hdr->asc == 0x29 && sense_hdr->ascq == 0x00)
			/*
			 * Unit Attention Code. This is the first IO
			 * to the new path, so just retry.
			 */
			return ADD_TO_MLQUEUE;
		break;
	}

	return SCSI_RETURN_NOT_HANDLED;
}