#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int bcr; } ;
struct i3c_dev_desc {TYPE_1__ info; } ;
struct i3c_bus {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct i3c_bus* dev_to_i3cbus (struct device*) ; 
 struct i3c_dev_desc* dev_to_i3cdesc (struct device*) ; 
 int /*<<< orphan*/  i3c_bus_normaluse_lock (struct i3c_bus*) ; 
 int /*<<< orphan*/  i3c_bus_normaluse_unlock (struct i3c_bus*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t bcr_show(struct device *dev,
			struct device_attribute *da,
			char *buf)
{
	struct i3c_bus *bus = dev_to_i3cbus(dev);
	struct i3c_dev_desc *desc;
	ssize_t ret;

	i3c_bus_normaluse_lock(bus);
	desc = dev_to_i3cdesc(dev);
	ret = sprintf(buf, "%x\n", desc->info.bcr);
	i3c_bus_normaluse_unlock(bus);

	return ret;
}