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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dpaa_eth_attrs ; 

void dpaa_eth_sysfs_init(struct device *dev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dpaa_eth_attrs); i++)
		if (device_create_file(dev, &dpaa_eth_attrs[i])) {
			dev_err(dev, "Error creating sysfs file\n");
			while (i > 0)
				device_remove_file(dev, &dpaa_eth_attrs[--i]);
			return;
		}
}