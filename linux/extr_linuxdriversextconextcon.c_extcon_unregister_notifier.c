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
struct extcon_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/ * nh; } ;

/* Variables and functions */
 int EINVAL ; 
 int find_cable_index_by_id (struct extcon_dev*,unsigned int) ; 
 int raw_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int extcon_unregister_notifier(struct extcon_dev *edev, unsigned int id,
				struct notifier_block *nb)
{
	unsigned long flags;
	int ret, idx;

	if (!edev || !nb)
		return -EINVAL;

	idx = find_cable_index_by_id(edev, id);
	if (idx < 0)
		return idx;

	spin_lock_irqsave(&edev->lock, flags);
	ret = raw_notifier_chain_unregister(&edev->nh[idx], nb);
	spin_unlock_irqrestore(&edev->lock, flags);

	return ret;
}