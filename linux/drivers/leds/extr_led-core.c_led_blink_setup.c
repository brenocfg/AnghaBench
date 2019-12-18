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
struct led_classdev {int /*<<< orphan*/  (* blink_set ) (struct led_classdev*,unsigned long*,unsigned long*) ;int /*<<< orphan*/  work_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_ONESHOT ; 
 int /*<<< orphan*/  led_set_software_blink (struct led_classdev*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct led_classdev*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void led_blink_setup(struct led_classdev *led_cdev,
		     unsigned long *delay_on,
		     unsigned long *delay_off)
{
	if (!test_bit(LED_BLINK_ONESHOT, &led_cdev->work_flags) &&
	    led_cdev->blink_set &&
	    !led_cdev->blink_set(led_cdev, delay_on, delay_off))
		return;

	/* blink with 1 Hz as default if nothing specified */
	if (!*delay_on && !*delay_off)
		*delay_on = *delay_off = 500;

	led_set_software_blink(led_cdev, *delay_on, *delay_off);
}