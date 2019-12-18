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
struct sd_info {int pre_cmd_err; int /*<<< orphan*/  sd_lock_status; int /*<<< orphan*/  sd_pass_thru_en; } ;
struct scsi_cmnd {int* cmnd; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  SD_SDR_RST ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_CHANGE ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_INVALID_CMD_FIELD ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_NOT_PRESENT ; 
 int STATUS_SUCCESS ; 
 int TRANSPORT_FAILED ; 
 int TRANSPORT_GOOD ; 
 int reset_sd (struct rtsx_chip*) ; 
 int reset_sd_card (struct rtsx_chip*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 

int sd_hw_rst(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	unsigned int lun = SCSI_LUN(srb);
	int retval;

	if (!sd_card->sd_pass_thru_en) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}

	if (sd_card->pre_cmd_err) {
		sd_card->pre_cmd_err = 0;
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		return TRANSPORT_FAILED;
	}

	if ((srb->cmnd[2] != 0x53) || (srb->cmnd[3] != 0x44) ||
	    (srb->cmnd[4] != 0x20) || (srb->cmnd[5] != 0x43) ||
	    (srb->cmnd[6] != 0x61) || (srb->cmnd[7] != 0x72) ||
	    (srb->cmnd[8] != 0x64)) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}

	switch (srb->cmnd[1] & 0x0F) {
	case 0:
#ifdef SUPPORT_SD_LOCK
		if (srb->cmnd[9] == 0x64)
			sd_card->sd_lock_status |= SD_SDR_RST;
#endif
		retval = reset_sd_card(chip);
		if (retval != STATUS_SUCCESS) {
#ifdef SUPPORT_SD_LOCK
			sd_card->sd_lock_status &= ~SD_SDR_RST;
#endif
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			sd_card->pre_cmd_err = 1;
			return TRANSPORT_FAILED;
		}
#ifdef SUPPORT_SD_LOCK
		sd_card->sd_lock_status &= ~SD_SDR_RST;
#endif
		break;

	case 1:
		retval = reset_sd(chip);
		if (retval != STATUS_SUCCESS) {
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			sd_card->pre_cmd_err = 1;
			return TRANSPORT_FAILED;
		}
		break;

	default:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}

	scsi_set_resid(srb, 0);
	return TRANSPORT_GOOD;
}