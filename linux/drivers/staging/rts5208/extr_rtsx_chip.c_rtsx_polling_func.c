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
struct rtsx_chip {int /*<<< orphan*/  sd_int; int /*<<< orphan*/  sd_io; scalar_t__ polling_config; } ;

/* Variables and functions */
 scalar_t__ CHECK_LUN_MODE (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTSX_STAT_DELINK ; 
#define  RTSX_STAT_IDLE 129 
#define  RTSX_STAT_RUN 128 
 int /*<<< orphan*/  RTSX_STAT_SS ; 
 int /*<<< orphan*/  RTSX_STAT_SUSPEND ; 
 int /*<<< orphan*/  SD_MS_2LUN ; 
 int /*<<< orphan*/  do_remaining_work (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_blink_led (struct rtsx_chip*) ; 
 scalar_t__ rtsx_chk_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_delink_stage (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_enable_aspm (struct rtsx_chip*) ; 
 int rtsx_get_stat (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cards (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_manage_1lun_mode (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_manage_2lun_mode (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_manage_aspm (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_manage_idle (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_manage_ocp (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_manage_sd_lock (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_manage_ss (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_read_config_byte (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_switch_sdio_ctrl (struct rtsx_chip*) ; 

void rtsx_polling_func(struct rtsx_chip *chip)
{
	if (rtsx_chk_stat(chip, RTSX_STAT_SUSPEND))
		return;

	if (rtsx_chk_stat(chip, RTSX_STAT_DELINK))
		goto delink_stage;

	if (chip->polling_config) {
		u8 val;

		rtsx_read_config_byte(chip, 0, &val);
	}

	if (rtsx_chk_stat(chip, RTSX_STAT_SS))
		return;

	rtsx_manage_ocp(chip);

	rtsx_manage_sd_lock(chip);

	rtsx_init_cards(chip);

	rtsx_manage_ss(chip);

	rtsx_manage_aspm(chip);

	rtsx_manage_idle(chip);

	switch (rtsx_get_stat(chip)) {
	case RTSX_STAT_RUN:
#if !defined(LED_AUTO_BLINK) && defined(REGULAR_BLINK)
		rtsx_blink_led(chip);
#endif
		do_remaining_work(chip);
		break;

	case RTSX_STAT_IDLE:
		if (chip->sd_io && !chip->sd_int)
			try_to_switch_sdio_ctrl(chip);

		rtsx_enable_aspm(chip);
		break;

	default:
		break;
	}

	if (CHECK_LUN_MODE(chip, SD_MS_2LUN))
		rtsx_manage_2lun_mode(chip);
	else
		rtsx_manage_1lun_mode(chip);

delink_stage:
	rtsx_delink_stage(chip);
}