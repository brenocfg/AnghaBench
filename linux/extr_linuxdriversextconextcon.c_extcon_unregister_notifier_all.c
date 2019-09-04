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
struct notifier_block {int dummy; } ;
struct extcon_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  nh_all; } ;

/* Variables and functions */
 int EINVAL ; 
 int raw_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int extcon_unregister_notifier_all(struct extcon_dev *edev,
				struct notifier_block *nb)
{
	unsigned long flags;
	int ret;

	if (!edev || !nb)
		return -EINVAL;

	spin_lock_irqsave(&edev->lock, flags);
	ret = raw_notifier_chain_unregister(&edev->nh_all, nb);
	spin_unlock_irqrestore(&edev->lock, flags);

	return ret;
}