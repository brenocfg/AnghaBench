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
struct TYPE_4__ {int /*<<< orphan*/ * lock; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lock; } ;
struct z8530_dev {int /*<<< orphan*/  lock; TYPE_2__ chanB; TYPE_1__ chanA; } ;

/* Variables and functions */
 int do_z8530_init (struct z8530_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int z8530_init(struct z8530_dev *dev)
{
	unsigned long flags;
	int ret;

	/* Set up the chip level lock */
	spin_lock_init(&dev->lock);
	dev->chanA.lock = &dev->lock;
	dev->chanB.lock = &dev->lock;

	spin_lock_irqsave(&dev->lock, flags);
	ret = do_z8530_init(dev);
	spin_unlock_irqrestore(&dev->lock, flags);

	return ret;
}