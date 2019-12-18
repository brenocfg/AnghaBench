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
struct scsi_cmnd {int* cmnd; } ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
#define  LOAD_MEDIUM 131 
#define  MAKE_MEDIUM_READY 130 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_NOT_PRESENT ; 
#define  STOP_MEDIUM 129 
 int TRANSPORT_ERROR ; 
 int TRANSPORT_FAILED ; 
 int TRANSPORT_GOOD ; 
#define  UNLOAD_MEDIUM 128 
 int /*<<< orphan*/  check_card_ready (struct rtsx_chip*,unsigned int) ; 
 int /*<<< orphan*/  eject_card (struct rtsx_chip*,unsigned int) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_stop_unit(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	unsigned int lun = SCSI_LUN(srb);

	scsi_set_resid(srb, scsi_bufflen(srb));

	if (srb->cmnd[1] == 1)
		return TRANSPORT_GOOD;

	switch (srb->cmnd[0x4]) {
	case STOP_MEDIUM:
		/* Media disabled */
		return TRANSPORT_GOOD;

	case UNLOAD_MEDIUM:
		/* Media shall be unload */
		if (check_card_ready(chip, lun))
			eject_card(chip, lun);
		return TRANSPORT_GOOD;

	case MAKE_MEDIUM_READY:
	case LOAD_MEDIUM:
		if (check_card_ready(chip, lun))
			return TRANSPORT_GOOD;
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		return TRANSPORT_FAILED;

		break;
	}

	return TRANSPORT_ERROR;
}