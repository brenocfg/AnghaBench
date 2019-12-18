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
struct xd_info {int xd_clock; } ;
struct sd_info {int sd_clock; } ;
struct scsi_cmnd {int* cmnd; } ;
struct ms_info {int ms_clock; } ;
struct rtsx_chip {int blink_led; scalar_t__ ss_en; struct ms_info ms_card; struct sd_info sd_card; struct xd_info xd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_GPIO ; 
#define  MS_CARD 130 
 int /*<<< orphan*/  RTSX_STAT_RUN ; 
 scalar_t__ RTSX_STAT_SS ; 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
#define  SD_CARD 129 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_INVALID_CMD_FIELD ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_WRITE_ERR ; 
 int /*<<< orphan*/  SSC_PDCTL ; 
 int STATUS_SUCCESS ; 
 int TRANSPORT_FAILED ; 
 int TRANSPORT_GOOD ; 
#define  XD_CARD 128 
 int /*<<< orphan*/  rtsx_disable_aspm (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_exit_ss (struct rtsx_chip*) ; 
 int rtsx_force_power_on (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtsx_get_stat (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turn_off_led (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static int set_variable(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	unsigned int lun = SCSI_LUN(srb);

	if (srb->cmnd[3] == 1) {
		/* Variable Clock */
		struct xd_info *xd_card = &chip->xd_card;
		struct sd_info *sd_card = &chip->sd_card;
		struct ms_info *ms_card = &chip->ms_card;

		switch (srb->cmnd[4]) {
		case XD_CARD:
			xd_card->xd_clock = srb->cmnd[5];
			break;

		case SD_CARD:
			sd_card->sd_clock = srb->cmnd[5];
			break;

		case MS_CARD:
			ms_card->ms_clock = srb->cmnd[5];
			break;

		default:
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			return TRANSPORT_FAILED;
		}
	} else if (srb->cmnd[3] == 2) {
		if (srb->cmnd[4]) {
			chip->blink_led = 1;
		} else {
			int retval;

			chip->blink_led = 0;

			rtsx_disable_aspm(chip);

			if (chip->ss_en &&
			    (rtsx_get_stat(chip) == RTSX_STAT_SS)) {
				rtsx_exit_ss(chip);
				wait_timeout(100);
			}
			rtsx_set_stat(chip, RTSX_STAT_RUN);

			retval = rtsx_force_power_on(chip, SSC_PDCTL);
			if (retval != STATUS_SUCCESS) {
				set_sense_type(chip, SCSI_LUN(srb),
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				return TRANSPORT_FAILED;
			}

			turn_off_led(chip, LED_GPIO);
		}
	} else {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}

	return TRANSPORT_GOOD;
}