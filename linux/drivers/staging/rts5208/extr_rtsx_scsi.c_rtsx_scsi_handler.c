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
typedef  int /*<<< orphan*/  u16 ;
struct sd_info {scalar_t__ sd_erase_status; } ;
struct scsi_cmnd {int* cmnd; } ;
struct ms_info {scalar_t__ format_status; scalar_t__ progress; } ;
struct rtsx_chip {struct ms_info ms_card; struct sd_info sd_card; } ;

/* Variables and functions */
#define  ALLOW_MEDIUM_REMOVAL 152 
#define  CMD_MSPRO_MG_RKEY 151 
#define  CMD_MSPRO_MG_SKEY 150 
 int /*<<< orphan*/  CUR_ERR ; 
 scalar_t__ FORMAT_IN_PROGRESS ; 
#define  FORMAT_UNIT 149 
 int GET_DEV_STATUS ; 
#define  INQUIRY 148 
#define  MODE_SELECT 147 
#define  MODE_SENSE 146 
#define  MODE_SENSE_10 145 
 scalar_t__ MS_CARD ; 
#define  MS_SP_CMND 144 
#define  READ_10 143 
#define  READ_6 142 
#define  READ_CAPACITY 141 
#define  REQUEST_SENSE 140 
 int SCSI_APP_CMD ; 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
#define  SD_EXECUTE_NO_DATA 139 
#define  SD_EXECUTE_READ 138 
#define  SD_EXECUTE_WRITE 137 
#define  SD_GET_RSP 136 
#define  SD_HW_RST 135 
#define  SD_PASS_THRU_MODE 134 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_INVALID_CMD_FIELD ; 
#define  START_STOP 133 
#define  TEST_UNIT_READY 132 
 int TRANSPORT_FAILED ; 
 int TRANSPORT_GOOD ; 
#define  VENDOR_CMND 131 
#define  VERIFY 130 
#define  WRITE_10 129 
#define  WRITE_6 128 
 int allow_medium_removal (struct scsi_cmnd*,struct rtsx_chip*) ; 
 scalar_t__ get_lun_card (struct rtsx_chip*,unsigned int) ; 
 int inquiry (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int /*<<< orphan*/  led_shine (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int mg_report_key (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int mg_send_key (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int mode_sense (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int ms_sp_cmnd (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_capacity (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_format_capacity (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_write (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int request_sense (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int sd_extension_cmnd (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int /*<<< orphan*/  set_sense_data (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int start_stop_unit (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int test_unit_ready (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int vendor_cmnd (struct scsi_cmnd*,struct rtsx_chip*) ; 

int rtsx_scsi_handler(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
#ifdef SUPPORT_SD_LOCK
	struct sd_info *sd_card = &chip->sd_card;
#endif
	struct ms_info *ms_card = &chip->ms_card;
	unsigned int lun = SCSI_LUN(srb);
	int result;

#ifdef SUPPORT_SD_LOCK
	if (sd_card->sd_erase_status) {
		/* Block all SCSI command except for
		 * REQUEST_SENSE and rs_ppstatus
		 */
		if (!((srb->cmnd[0] == VENDOR_CMND) &&
		      (srb->cmnd[1] == SCSI_APP_CMD) &&
		      (srb->cmnd[2] == GET_DEV_STATUS)) &&
		      (srb->cmnd[0] != REQUEST_SENSE)) {
			/* Logical Unit Not Ready Format in Progress */
			set_sense_data(chip, lun, CUR_ERR,
				       0x02, 0, 0x04, 0x04, 0, 0);
			return TRANSPORT_FAILED;
		}
	}
#endif

	if ((get_lun_card(chip, lun) == MS_CARD) &&
	    (ms_card->format_status == FORMAT_IN_PROGRESS)) {
		if ((srb->cmnd[0] != REQUEST_SENSE) &&
		    (srb->cmnd[0] != INQUIRY)) {
			/* Logical Unit Not Ready Format in Progress */
			set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x04, 0x04,
				       0, (u16)(ms_card->progress));
			return TRANSPORT_FAILED;
		}
	}

	switch (srb->cmnd[0]) {
	case READ_10:
	case WRITE_10:
	case READ_6:
	case WRITE_6:
		result = read_write(srb, chip);
#if !defined(LED_AUTO_BLINK) && !defined(REGULAR_BLINK)
		led_shine(srb, chip);
#endif
		break;

	case TEST_UNIT_READY:
		result = test_unit_ready(srb, chip);
		break;

	case INQUIRY:
		result = inquiry(srb, chip);
		break;

	case READ_CAPACITY:
		result = read_capacity(srb, chip);
		break;

	case START_STOP:
		result = start_stop_unit(srb, chip);
		break;

	case ALLOW_MEDIUM_REMOVAL:
		result = allow_medium_removal(srb, chip);
		break;

	case REQUEST_SENSE:
		result = request_sense(srb, chip);
		break;

	case MODE_SENSE:
	case MODE_SENSE_10:
		result = mode_sense(srb, chip);
		break;

	case 0x23:
		result = read_format_capacity(srb, chip);
		break;

	case VENDOR_CMND:
		result = vendor_cmnd(srb, chip);
		break;

	case MS_SP_CMND:
		result = ms_sp_cmnd(srb, chip);
		break;

#ifdef SUPPORT_CPRM
	case SD_PASS_THRU_MODE:
	case SD_EXECUTE_NO_DATA:
	case SD_EXECUTE_READ:
	case SD_EXECUTE_WRITE:
	case SD_GET_RSP:
	case SD_HW_RST:
		result = sd_extension_cmnd(srb, chip);
		break;
#endif

#ifdef SUPPORT_MAGIC_GATE
	case CMD_MSPRO_MG_RKEY:
		result = mg_report_key(srb, chip);
		break;

	case CMD_MSPRO_MG_SKEY:
		result = mg_send_key(srb, chip);
		break;
#endif

	case FORMAT_UNIT:
	case MODE_SELECT:
	case VERIFY:
		result = TRANSPORT_GOOD;
		break;

	default:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		result = TRANSPORT_FAILED;
	}

	return result;
}