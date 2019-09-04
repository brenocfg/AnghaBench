#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {void* expires; } ;

/* Variables and functions */
 int FSHIFT ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int* avenrun ; 
 void* jiffies ; 
 TYPE_1__ led_blink_timer ; 
 unsigned long led_blink_timer_timeout ; 
 int /*<<< orphan*/  led_toggle () ; 

__attribute__((used)) static void led_blink(struct timer_list *unused)
{
	unsigned long timeout = led_blink_timer_timeout;

	led_toggle();

	/* reschedule */
	if (!timeout) { /* blink according to load */
		led_blink_timer.expires = jiffies +
			((1 + (avenrun[0] >> FSHIFT)) * HZ);
	} else { /* blink at user specified interval */
		led_blink_timer.expires = jiffies + (timeout * HZ);
	}
	add_timer(&led_blink_timer);
}