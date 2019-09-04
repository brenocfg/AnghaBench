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
struct edac_device_ctl_info {int /*<<< orphan*/  sysfs_attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpc85xx_l2_sysfs_attributes ; 

__attribute__((used)) static void mpc85xx_set_l2_sysfs_attributes(struct edac_device_ctl_info
					    *edac_dev)
{
	edac_dev->sysfs_attributes = mpc85xx_l2_sysfs_attributes;
}