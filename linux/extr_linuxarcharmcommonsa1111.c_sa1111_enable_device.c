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
struct sa1111_dev {unsigned int skpcr_mask; int /*<<< orphan*/  devid; } ;
struct sa1111 {int /*<<< orphan*/  lock; scalar_t__ base; TYPE_1__* pdata; } ;
struct TYPE_2__ {int (* enable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ SA1111_SKPCR ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 struct sa1111* sa1111_chip_driver (struct sa1111_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

int sa1111_enable_device(struct sa1111_dev *sadev)
{
	struct sa1111 *sachip = sa1111_chip_driver(sadev);
	unsigned long flags;
	unsigned int val;
	int ret = 0;

	if (sachip->pdata && sachip->pdata->enable)
		ret = sachip->pdata->enable(sachip->pdata->data, sadev->devid);

	if (ret == 0) {
		spin_lock_irqsave(&sachip->lock, flags);
		val = readl_relaxed(sachip->base + SA1111_SKPCR);
		writel_relaxed(val | sadev->skpcr_mask, sachip->base + SA1111_SKPCR);
		spin_unlock_irqrestore(&sachip->lock, flags);
	}
	return ret;
}