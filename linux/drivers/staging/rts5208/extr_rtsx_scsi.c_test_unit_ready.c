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
struct sd_info {int sd_lock_status; scalar_t__ sd_lock_notify; } ;
struct scsi_cmnd {int dummy; } ;
struct rtsx_chip {struct sd_info sd_card; int /*<<< orphan*/  lun_mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
 scalar_t__ SD_CARD ; 
 int SD_LOCKED ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_CHANGE ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_NOT_PRESENT ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_READ_FORBIDDEN ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int TRANSPORT_FAILED ; 
 int TRANSPORT_GOOD ; 
 int /*<<< orphan*/  check_card_ready (struct rtsx_chip*,unsigned int) ; 
 scalar_t__ get_lun_card (struct rtsx_chip*,unsigned int) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_unit_ready(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	unsigned int lun = SCSI_LUN(srb);

	if (!check_card_ready(chip, lun)) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		return TRANSPORT_FAILED;
	}

	if (!(CHK_BIT(chip->lun_mc, lun))) {
		SET_BIT(chip->lun_mc, lun);
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		return TRANSPORT_FAILED;
	}

#ifdef SUPPORT_SD_LOCK
	if (get_lun_card(chip, SCSI_LUN(srb)) == SD_CARD) {
		struct sd_info *sd_card = &chip->sd_card;

		if (sd_card->sd_lock_notify) {
			sd_card->sd_lock_notify = 0;
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
			return TRANSPORT_FAILED;
		} else if (sd_card->sd_lock_status & SD_LOCKED) {
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_READ_FORBIDDEN);
			return TRANSPORT_FAILED;
		}
	}
#endif

	return TRANSPORT_GOOD;
}