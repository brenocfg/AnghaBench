#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct ipr_resource_entry {int dummy; } ;
struct TYPE_13__ {scalar_t__ failing_lba; } ;
struct TYPE_12__ {scalar_t__ failing_lba_hi; scalar_t__ failing_lba_lo; } ;
struct TYPE_14__ {TYPE_6__ dasd; TYPE_5__ vset; } ;
struct TYPE_11__ {scalar_t__ ioasc; scalar_t__ ioasc_specific; } ;
struct ipr_ioasa {TYPE_7__ u; TYPE_4__ hdr; } ;
struct TYPE_9__ {struct ipr_ioasa ioasa; } ;
struct ipr_cmnd {TYPE_3__* scsi_cmd; TYPE_2__ s; } ;
struct TYPE_10__ {int* sense_buffer; int /*<<< orphan*/  result; TYPE_1__* device; } ;
struct TYPE_8__ {struct ipr_resource_entry* hostdata; } ;

/* Variables and functions */
 int IPR_FIELD_POINTER_MASK ; 
 int IPR_FIELD_POINTER_VALID ; 
 scalar_t__ IPR_FIRST_DRIVER_IOASC ; 
 scalar_t__ IPR_IOASC_MED_DO_NOT_REALLOC ; 
 int IPR_IOASC_SENSE_CODE (scalar_t__) ; 
 int IPR_IOASC_SENSE_KEY (scalar_t__) ; 
 int IPR_IOASC_SENSE_QUAL (scalar_t__) ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int be32_to_cpu (scalar_t__) ; 
 scalar_t__ ipr_is_vset_device (struct ipr_resource_entry*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipr_gen_sense(struct ipr_cmnd *ipr_cmd)
{
	u32 failing_lba;
	u8 *sense_buf = ipr_cmd->scsi_cmd->sense_buffer;
	struct ipr_resource_entry *res = ipr_cmd->scsi_cmd->device->hostdata;
	struct ipr_ioasa *ioasa = &ipr_cmd->s.ioasa;
	u32 ioasc = be32_to_cpu(ioasa->hdr.ioasc);

	memset(sense_buf, 0, SCSI_SENSE_BUFFERSIZE);

	if (ioasc >= IPR_FIRST_DRIVER_IOASC)
		return;

	ipr_cmd->scsi_cmd->result = SAM_STAT_CHECK_CONDITION;

	if (ipr_is_vset_device(res) &&
	    ioasc == IPR_IOASC_MED_DO_NOT_REALLOC &&
	    ioasa->u.vset.failing_lba_hi != 0) {
		sense_buf[0] = 0x72;
		sense_buf[1] = IPR_IOASC_SENSE_KEY(ioasc);
		sense_buf[2] = IPR_IOASC_SENSE_CODE(ioasc);
		sense_buf[3] = IPR_IOASC_SENSE_QUAL(ioasc);

		sense_buf[7] = 12;
		sense_buf[8] = 0;
		sense_buf[9] = 0x0A;
		sense_buf[10] = 0x80;

		failing_lba = be32_to_cpu(ioasa->u.vset.failing_lba_hi);

		sense_buf[12] = (failing_lba & 0xff000000) >> 24;
		sense_buf[13] = (failing_lba & 0x00ff0000) >> 16;
		sense_buf[14] = (failing_lba & 0x0000ff00) >> 8;
		sense_buf[15] = failing_lba & 0x000000ff;

		failing_lba = be32_to_cpu(ioasa->u.vset.failing_lba_lo);

		sense_buf[16] = (failing_lba & 0xff000000) >> 24;
		sense_buf[17] = (failing_lba & 0x00ff0000) >> 16;
		sense_buf[18] = (failing_lba & 0x0000ff00) >> 8;
		sense_buf[19] = failing_lba & 0x000000ff;
	} else {
		sense_buf[0] = 0x70;
		sense_buf[2] = IPR_IOASC_SENSE_KEY(ioasc);
		sense_buf[12] = IPR_IOASC_SENSE_CODE(ioasc);
		sense_buf[13] = IPR_IOASC_SENSE_QUAL(ioasc);

		/* Illegal request */
		if ((IPR_IOASC_SENSE_KEY(ioasc) == 0x05) &&
		    (be32_to_cpu(ioasa->hdr.ioasc_specific) & IPR_FIELD_POINTER_VALID)) {
			sense_buf[7] = 10;	/* additional length */

			/* IOARCB was in error */
			if (IPR_IOASC_SENSE_CODE(ioasc) == 0x24)
				sense_buf[15] = 0xC0;
			else	/* Parameter data was invalid */
				sense_buf[15] = 0x80;

			sense_buf[16] =
			    ((IPR_FIELD_POINTER_MASK &
			      be32_to_cpu(ioasa->hdr.ioasc_specific)) >> 8) & 0xff;
			sense_buf[17] =
			    (IPR_FIELD_POINTER_MASK &
			     be32_to_cpu(ioasa->hdr.ioasc_specific)) & 0xff;
		} else {
			if (ioasc == IPR_IOASC_MED_DO_NOT_REALLOC) {
				if (ipr_is_vset_device(res))
					failing_lba = be32_to_cpu(ioasa->u.vset.failing_lba_lo);
				else
					failing_lba = be32_to_cpu(ioasa->u.dasd.failing_lba);

				sense_buf[0] |= 0x80;	/* Or in the Valid bit */
				sense_buf[3] = (failing_lba & 0xff000000) >> 24;
				sense_buf[4] = (failing_lba & 0x00ff0000) >> 16;
				sense_buf[5] = (failing_lba & 0x0000ff00) >> 8;
				sense_buf[6] = failing_lba & 0x000000ff;
			}

			sense_buf[7] = 6;	/* additional length */
		}
	}
}