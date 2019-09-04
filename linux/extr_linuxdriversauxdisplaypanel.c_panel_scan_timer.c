#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  charlcd; scalar_t__ initialized; scalar_t__ enabled; } ;

/* Variables and functions */
 scalar_t__ INPUT_POLL_TIME ; 
 int /*<<< orphan*/  charlcd_poke (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inputs_stable ; 
 scalar_t__ jiffies ; 
 TYPE_2__ keypad ; 
 scalar_t__ keypad_initialized ; 
 scalar_t__ keypressed ; 
 TYPE_1__ lcd ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  panel_process_inputs () ; 
 scalar_t__ phys_curr ; 
 scalar_t__ phys_prev ; 
 int /*<<< orphan*/  phys_scan_contacts () ; 
 int /*<<< orphan*/  pprt_lock ; 
 int /*<<< orphan*/  scan_timer ; 
 scalar_t__ spin_trylock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void panel_scan_timer(struct timer_list *unused)
{
	if (keypad.enabled && keypad_initialized) {
		if (spin_trylock_irq(&pprt_lock)) {
			phys_scan_contacts();

			/* no need for the parport anymore */
			spin_unlock_irq(&pprt_lock);
		}

		if (!inputs_stable || phys_curr != phys_prev)
			panel_process_inputs();
	}

	if (keypressed && lcd.enabled && lcd.initialized)
		charlcd_poke(lcd.charlcd);

	mod_timer(&scan_timer, jiffies + INPUT_POLL_TIME);
}