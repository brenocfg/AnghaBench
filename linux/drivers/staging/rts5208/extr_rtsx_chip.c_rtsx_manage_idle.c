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
struct rtsx_chip {scalar_t__ idle_counter; int /*<<< orphan*/  sd_io; int /*<<< orphan*/  card_ready; scalar_t__ auto_power_down; scalar_t__ led_toggle_counter; } ;

/* Variables and functions */
 scalar_t__ IDLE_MAX_COUNT ; 
 int /*<<< orphan*/  LED_GPIO ; 
 int OC_PDCTL ; 
 scalar_t__ RTSX_STAT_IDLE ; 
 int SSC_PDCTL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_force_power_down (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  rtsx_force_power_on (struct rtsx_chip*,int) ; 
 scalar_t__ rtsx_get_stat (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,scalar_t__) ; 
 int /*<<< orphan*/  turn_off_led (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtsx_manage_idle(struct rtsx_chip *chip)
{
	if (chip->idle_counter < IDLE_MAX_COUNT) {
		chip->idle_counter++;
		return;
	}

	if (rtsx_get_stat(chip) == RTSX_STAT_IDLE)
		return;

	dev_dbg(rtsx_dev(chip), "Idle state!\n");
	rtsx_set_stat(chip, RTSX_STAT_IDLE);

#if !defined(LED_AUTO_BLINK) && defined(REGULAR_BLINK)
	chip->led_toggle_counter = 0;
#endif
	rtsx_force_power_on(chip, SSC_PDCTL);

	turn_off_led(chip, LED_GPIO);

	if (chip->auto_power_down && !chip->card_ready && !chip->sd_io)
		rtsx_force_power_down(chip, SSC_PDCTL | OC_PDCTL);
}