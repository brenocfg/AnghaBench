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

/* Variables and functions */
 unsigned long BLINK_DELAY ; 
 int /*<<< orphan*/  led_trigger_blink_oneshot (int /*<<< orphan*/ ,unsigned long*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledtrig_mtd ; 
 int /*<<< orphan*/  ledtrig_nand ; 

void ledtrig_mtd_activity(void)
{
	unsigned long blink_delay = BLINK_DELAY;

	led_trigger_blink_oneshot(ledtrig_mtd,
				  &blink_delay, &blink_delay, 0);
	led_trigger_blink_oneshot(ledtrig_nand,
				  &blink_delay, &blink_delay, 0);
}