#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpwd {int /*<<< orphan*/  lock; TYPE_1__* devs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  runstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 size_t WD0_ID ; 
 int /*<<< orphan*/  WD_STAT_SVCD ; 
 int /*<<< orphan*/  cpwd_stoptimer (struct cpwd*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cpwd_interrupt(int irq, void *dev_id)
{
	struct cpwd *p = dev_id;

	/* Only WD0 will interrupt-- others are NMI and we won't
	 * see them here....
	 */
	spin_lock_irq(&p->lock);

	cpwd_stoptimer(p, WD0_ID);
	p->devs[WD0_ID].runstatus |=  WD_STAT_SVCD;

	spin_unlock_irq(&p->lock);

	return IRQ_HANDLED;
}