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
struct led_trigger {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_trigger_blink_setup (struct led_trigger*,unsigned long*,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void led_trigger_blink(struct led_trigger *trig,
		       unsigned long *delay_on,
		       unsigned long *delay_off)
{
	led_trigger_blink_setup(trig, delay_on, delay_off, 0, 0);
}