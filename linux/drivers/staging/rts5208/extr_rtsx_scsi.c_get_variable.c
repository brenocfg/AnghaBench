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
typedef  int /*<<< orphan*/  u8 ;
struct xd_info {int /*<<< orphan*/  xd_clock; } ;
struct sd_info {int /*<<< orphan*/  sd_clock; } ;
struct scsi_cmnd {int* cmnd; } ;
struct ms_info {int /*<<< orphan*/  ms_clock; } ;
struct rtsx_chip {int /*<<< orphan*/  blink_led; struct ms_info ms_card; struct sd_info sd_card; struct xd_info xd_card; } ;

/* Variables and functions */
#define  MS_CARD 130 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
#define  SD_CARD 129 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_INVALID_CMD_FIELD ; 
 int TRANSPORT_FAILED ; 
 int TRANSPORT_GOOD ; 
#define  XD_CARD 128 
 int /*<<< orphan*/  rtsx_stor_set_xfer_buf (int /*<<< orphan*/ *,int,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_variable(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	unsigned int lun = SCSI_LUN(srb);

	if (srb->cmnd[3] == 1) {
		struct xd_info *xd_card = &chip->xd_card;
		struct sd_info *sd_card = &chip->sd_card;
		struct ms_info *ms_card = &chip->ms_card;
		u8 tmp;

		switch (srb->cmnd[4]) {
		case XD_CARD:
			tmp = (u8)(xd_card->xd_clock);
			break;

		case SD_CARD:
			tmp = (u8)(sd_card->sd_clock);
			break;

		case MS_CARD:
			tmp = (u8)(ms_card->ms_clock);
			break;

		default:
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			return TRANSPORT_FAILED;
		}

		rtsx_stor_set_xfer_buf(&tmp, 1, srb);
	} else if (srb->cmnd[3] == 2) {
		u8 tmp = chip->blink_led;

		rtsx_stor_set_xfer_buf(&tmp, 1, srb);
	} else {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}

	return TRANSPORT_GOOD;
}