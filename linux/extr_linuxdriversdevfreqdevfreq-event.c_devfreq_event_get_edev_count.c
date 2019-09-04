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
typedef  int /*<<< orphan*/  u32 ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int of_property_count_elems_of_size (int /*<<< orphan*/ ,char*,int) ; 

int devfreq_event_get_edev_count(struct device *dev)
{
	int count;

	if (!dev->of_node) {
		dev_err(dev, "device does not have a device node entry\n");
		return -EINVAL;
	}

	count = of_property_count_elems_of_size(dev->of_node, "devfreq-events",
						sizeof(u32));
	if (count < 0) {
		dev_err(dev,
			"failed to get the count of devfreq-event in %pOF node\n",
			dev->of_node);
		return count;
	}

	return count;
}