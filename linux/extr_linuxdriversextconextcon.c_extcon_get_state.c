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
struct extcon_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int find_cable_index_by_id (struct extcon_dev*,unsigned int const) ; 
 int is_extcon_attached (struct extcon_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int extcon_get_state(struct extcon_dev *edev, const unsigned int id)
{
	int index, state;
	unsigned long flags;

	if (!edev)
		return -EINVAL;

	index = find_cable_index_by_id(edev, id);
	if (index < 0)
		return index;

	spin_lock_irqsave(&edev->lock, flags);
	state = is_extcon_attached(edev, index);
	spin_unlock_irqrestore(&edev->lock, flags);

	return state;
}