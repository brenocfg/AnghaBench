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
struct device {int dummy; } ;

/* Variables and functions */
 int device_for_each_child (struct device*,int /*<<< orphan*/ *,int (*) (struct device*,void*)) ; 
 int device_may_wakeup (struct device*) ; 

__attribute__((used)) static int zynqmp_gpd_is_active_wakeup_path(struct device *dev, void *not_used)
{
	int may_wakeup;

	may_wakeup = device_may_wakeup(dev);
	if (may_wakeup)
		return may_wakeup;

	return device_for_each_child(dev, NULL,
			zynqmp_gpd_is_active_wakeup_path);
}