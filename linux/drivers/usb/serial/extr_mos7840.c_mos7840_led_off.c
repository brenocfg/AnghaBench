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
struct timer_list {int dummy; } ;
struct moschip_port {int /*<<< orphan*/  led_timer2; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF_MS ; 
 int /*<<< orphan*/  MODEM_CONTROL_REGISTER ; 
 struct moschip_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  led_timer1 ; 
 struct moschip_port* mcs ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mos7840_set_led_async (struct moschip_port*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mos7840_led_off(struct timer_list *t)
{
	struct moschip_port *mcs = from_timer(mcs, t, led_timer1);

	/* Turn off LED */
	mos7840_set_led_async(mcs, 0x0300, MODEM_CONTROL_REGISTER);
	mod_timer(&mcs->led_timer2,
				jiffies + msecs_to_jiffies(LED_OFF_MS));
}