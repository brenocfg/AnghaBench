#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_fuse_info {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {unsigned int size; } ;

/* Variables and functions */
 int device_create_bin_file (struct device*,TYPE_1__*) ; 
 TYPE_1__ fuse_bin_attr ; 

__attribute__((used)) static int tegra_fuse_create_sysfs(struct device *dev, unsigned int size,
				   const struct tegra_fuse_info *info)
{
	fuse_bin_attr.size = size;

	return device_create_bin_file(dev, &fuse_bin_attr);
}