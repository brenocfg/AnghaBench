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
struct nsim_bus_dev {int num_vfs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct nsim_bus_dev* to_nsim_bus_dev (struct device*) ; 

__attribute__((used)) static ssize_t
nsim_bus_dev_numvfs_show(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	struct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	return sprintf(buf, "%u\n", nsim_bus_dev->num_vfs);
}