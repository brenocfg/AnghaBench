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
struct moschip_port {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOS7840_FLAG_LED_BUSY ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct moschip_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_timer2 ; 
 struct moschip_port* mcs ; 

__attribute__((used)) static void mos7840_led_flag_off(struct timer_list *t)
{
	struct moschip_port *mcs = from_timer(mcs, t, led_timer2);

	clear_bit_unlock(MOS7840_FLAG_LED_BUSY, &mcs->flags);
}