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
struct fotg210_hcd {int /*<<< orphan*/  lock; int /*<<< orphan*/  rh_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOTG210_RH_HALTED ; 
 int /*<<< orphan*/  fotg210_halt (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_turn_off_all_ports (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fotg210_silence_controller(struct fotg210_hcd *fotg210)
{
	fotg210_halt(fotg210);

	spin_lock_irq(&fotg210->lock);
	fotg210->rh_state = FOTG210_RH_HALTED;
	fotg210_turn_off_all_ports(fotg210);
	spin_unlock_irq(&fotg210->lock);
}