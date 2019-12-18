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
typedef  int u8 ;
struct scsi_cmnd {int* cmnd; } ;
struct ms_info {int mg_entry_num; } ;
struct rtsx_chip {scalar_t__ ss_en; struct ms_info ms_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_MSPRO (struct ms_info*) ; 
 int KC_MG_R_PRO ; 
#define  KF_CHG_HOST 131 
#define  KF_RSP_HOST 130 
#define  KF_SET_ICV 129 
#define  KF_SET_LEAF_ID 128 
 scalar_t__ MS_CARD ; 
 int /*<<< orphan*/  RTSX_STAT_RUN ; 
 scalar_t__ RTSX_STAT_SS ; 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_INVALID_CMD_FIELD ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_NOT_PRESENT ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_WRITE_PROTECT ; 
 int /*<<< orphan*/  SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM ; 
 int STATUS_SUCCESS ; 
 int TRANSPORT_FAILED ; 
 int TRANSPORT_GOOD ; 
 int /*<<< orphan*/  check_card_ready (struct rtsx_chip*,unsigned int) ; 
 scalar_t__ check_card_wp (struct rtsx_chip*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ get_lun_card (struct rtsx_chip*,unsigned int) ; 
 int mg_chg (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int mg_rsp (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int mg_set_ICV (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int mg_set_leaf_id (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int /*<<< orphan*/  ms_cleanup_work (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_disable_aspm (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_exit_ss (struct rtsx_chip*) ; 
 scalar_t__ rtsx_get_stat (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static int mg_send_key(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;
	unsigned int lun = SCSI_LUN(srb);
	int retval;
	u8 key_format;

	rtsx_disable_aspm(chip);

	if (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) {
		rtsx_exit_ss(chip);
		wait_timeout(100);
	}
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	ms_cleanup_work(chip);

	if (!check_card_ready(chip, lun)) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		return TRANSPORT_FAILED;
	}
	if (check_card_wp(chip, lun)) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_WRITE_PROTECT);
		return TRANSPORT_FAILED;
	}
	if (get_lun_card(chip, lun) != MS_CARD) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT);
		return TRANSPORT_FAILED;
	}

	if (srb->cmnd[7] != KC_MG_R_PRO) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}

	if (!CHK_MSPRO(ms_card)) {
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		return TRANSPORT_FAILED;
	}

	key_format = srb->cmnd[10] & 0x3F;
	dev_dbg(rtsx_dev(chip), "key_format = 0x%x\n", key_format);

	switch (key_format) {
	case KF_SET_LEAF_ID:
		if ((scsi_bufflen(srb) == 0x0C) &&
		    (srb->cmnd[8] == 0x00) &&
		    (srb->cmnd[9] == 0x0C)) {
			retval = mg_set_leaf_id(srb, chip);
			if (retval != STATUS_SUCCESS)
				return TRANSPORT_FAILED;

		} else {
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			return TRANSPORT_FAILED;
		}
		break;

	case KF_CHG_HOST:
		if ((scsi_bufflen(srb) == 0x0C) &&
		    (srb->cmnd[8] == 0x00) &&
		    (srb->cmnd[9] == 0x0C)) {
			retval = mg_chg(srb, chip);
			if (retval != STATUS_SUCCESS)
				return TRANSPORT_FAILED;

		} else {
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			return TRANSPORT_FAILED;
		}
		break;

	case KF_RSP_HOST:
		if ((scsi_bufflen(srb) == 0x0C) &&
		    (srb->cmnd[8] == 0x00) &&
		    (srb->cmnd[9] == 0x0C)) {
			retval = mg_rsp(srb, chip);
			if (retval != STATUS_SUCCESS)
				return TRANSPORT_FAILED;

		} else {
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			return TRANSPORT_FAILED;
		}
		break;

	case KF_SET_ICV:
		ms_card->mg_entry_num = srb->cmnd[5];
		if ((scsi_bufflen(srb) == 0x404) &&
		    (srb->cmnd[8] == 0x04) &&
		    (srb->cmnd[9] == 0x04) &&
		    (srb->cmnd[2] == 0x00) &&
		    (srb->cmnd[3] == 0x00) &&
		    (srb->cmnd[4] == 0x00) &&
		    (srb->cmnd[5] < 32)) {
			retval = mg_set_ICV(srb, chip);
			if (retval != STATUS_SUCCESS)
				return TRANSPORT_FAILED;

		} else {
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
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