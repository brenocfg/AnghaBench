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
struct tw5864_dev {int /*<<< orphan*/  slock; scalar_t__ irqmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tw5864_irqmask_apply (struct tw5864_dev*) ; 

__attribute__((used)) static void tw5864_interrupts_disable(struct tw5864_dev *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->slock, flags);
	dev->irqmask = 0;
	tw5864_irqmask_apply(dev);
	spin_unlock_irqrestore(&dev->slock, flags);
}