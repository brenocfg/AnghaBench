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
struct device_node {int dummy; } ;

/* Variables and functions */
 int __of_device_is_compatible (struct device_node const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devtree_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int of_device_is_compatible(const struct device_node *device,
		const char *compat)
{
	unsigned long flags;
	int res;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	res = __of_device_is_compatible(device, compat, NULL, NULL);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	return res;
}