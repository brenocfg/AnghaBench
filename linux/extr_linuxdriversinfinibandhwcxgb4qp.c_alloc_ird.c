#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {TYPE_3__ lldi; } ;
struct c4iw_dev {scalar_t__ avail_ird; TYPE_2__ rdev; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_ird(struct c4iw_dev *dev, u32 ird)
{
	int ret = 0;

	spin_lock_irq(&dev->lock);
	if (ird <= dev->avail_ird)
		dev->avail_ird -= ird;
	else
		ret = -ENOMEM;
	spin_unlock_irq(&dev->lock);

	if (ret)
		dev_warn(&dev->rdev.lldi.pdev->dev,
			 "device IRD resources exhausted\n");

	return ret;
}