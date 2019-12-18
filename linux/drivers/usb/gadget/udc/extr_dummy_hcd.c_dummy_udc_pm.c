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
struct dummy_hcd {int dummy; } ;
struct dummy {int udc_suspended; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_link_state (struct dummy_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dummy_udc_pm(struct dummy *dum, struct dummy_hcd *dum_hcd,
		int suspend)
{
	spin_lock_irq(&dum->lock);
	dum->udc_suspended = suspend;
	set_link_state(dum_hcd);
	spin_unlock_irq(&dum->lock);
}