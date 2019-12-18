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
struct pasid_state {int /*<<< orphan*/  count; } ;
struct device_state {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct pasid_state** __get_pasid_state_ptr (struct device_state*,int,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct pasid_state *get_pasid_state(struct device_state *dev_state,
					   int pasid)
{
	struct pasid_state **ptr, *ret = NULL;
	unsigned long flags;

	spin_lock_irqsave(&dev_state->lock, flags);
	ptr = __get_pasid_state_ptr(dev_state, pasid, false);

	if (ptr == NULL)
		goto out_unlock;

	ret = *ptr;
	if (ret)
		atomic_inc(&ret->count);

out_unlock:
	spin_unlock_irqrestore(&dev_state->lock, flags);

	return ret;
}