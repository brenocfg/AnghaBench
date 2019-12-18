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
struct rtsx_chip {scalar_t__ ss_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTSX_STAT_RUN ; 
 scalar_t__ RTSX_STAT_SS ; 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
 scalar_t__ SD_CARD ; 
#define  SD_EXECUTE_NO_DATA 133 
#define  SD_EXECUTE_READ 132 
#define  SD_EXECUTE_WRITE 131 
#define  SD_GET_RSP 130 
#define  SD_HW_RST 129 
#define  SD_PASS_THRU_MODE 128 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_INVALID_CMD_FIELD ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_NOT_PRESENT ; 
 int TRANSPORT_FAILED ; 
 int /*<<< orphan*/  check_card_ready (struct rtsx_chip*,unsigned int) ; 
 scalar_t__ get_lun_card (struct rtsx_chip*,unsigned int) ; 
 int /*<<< orphan*/  rtsx_disable_aspm (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_exit_ss (struct rtsx_chip*) ; 
 scalar_t__ rtsx_get_stat (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_cleanup_work (struct rtsx_chip*) ; 
 int sd_execute_no_data (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int sd_execute_read_data (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int sd_execute_write_data (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int sd_get_cmd_rsp (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int sd_hw_rst (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int sd_pass_thru_mode (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static int sd_extension_cmnd(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	unsigned int lun = SCSI_LUN(srb);
	int result;

	rtsx_disable_aspm(chip);

	if (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) {
		rtsx_exit_ss(chip);
		wait_timeout(100);
	}
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	sd_cleanup_work(chip);

	if (!check_card_ready(chip, lun)) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		return TRANSPORT_FAILED;
	}
	if (get_lun_card(chip, lun) != SD_CARD) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT);
		return TRANSPORT_FAILED;
	}

	switch (srb->cmnd[0]) {
	case SD_PASS_THRU_MODE:
		result = sd_pass_thru_mode(srb, chip);
		break;

	case SD_EXECUTE_NO_DATA:
		result = sd_execute_no_data(srb, chip);
		break;

	case SD_EXECUTE_READ:
		result = sd_execute_read_data(srb, chip);
		break;

	case SD_EXECUTE_WRITE:
		result = sd_execute_write_data(srb, chip);
		break;

	case SD_GET_RSP:
		result = sd_get_cmd_rsp(srb, chip);
		break;

	case SD_HW_RST:
		result = sd_hw_rst(srb, chip);
		break;

	default:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}

	return result;
}