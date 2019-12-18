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
struct brcms_info {int /*<<< orphan*/  isr_lock; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  wlc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ brcms_c_isr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t brcms_isr(int irq, void *dev_id)
{
	struct brcms_info *wl;
	irqreturn_t ret = IRQ_NONE;

	wl = (struct brcms_info *) dev_id;

	spin_lock(&wl->isr_lock);

	/* call common first level interrupt handler */
	if (brcms_c_isr(wl->wlc)) {
		/* schedule second level handler */
		tasklet_schedule(&wl->tasklet);
		ret = IRQ_HANDLED;
	}

	spin_unlock(&wl->isr_lock);

	return ret;
}