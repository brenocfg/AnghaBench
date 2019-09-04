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
struct pasid_state {int dummy; } ;
struct device_state {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct pasid_state** __get_pasid_state_ptr (struct device_state*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int set_pasid_state(struct device_state *dev_state,
			   struct pasid_state *pasid_state,
			   int pasid)
{
	struct pasid_state **ptr;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&dev_state->lock, flags);
	ptr = __get_pasid_state_ptr(dev_state, pasid, true);

	ret = -ENOMEM;
	if (ptr == NULL)
		goto out_unlock;

	ret = -ENOMEM;
	if (*ptr != NULL)
		goto out_unlock;

	*ptr = pasid_state;

	ret = 0;

out_unlock:
	spin_unlock_irqrestore(&dev_state->lock, flags);

	return ret;
}