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
struct TYPE_2__ {int /*<<< orphan*/  i3c; } ;
struct i3c_bus {TYPE_1__ scl_rate; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct i3c_bus* dev_to_i3cbus (struct device*) ; 
 int /*<<< orphan*/  i3c_bus_normaluse_lock (struct i3c_bus*) ; 
 int /*<<< orphan*/  i3c_bus_normaluse_unlock (struct i3c_bus*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t i3c_scl_frequency_show(struct device *dev,
				      struct device_attribute *da,
				      char *buf)
{
	struct i3c_bus *i3cbus = dev_to_i3cbus(dev);
	ssize_t ret;

	i3c_bus_normaluse_lock(i3cbus);
	ret = sprintf(buf, "%ld\n", i3cbus->scl_rate.i3c);
	i3c_bus_normaluse_unlock(i3cbus);

	return ret;
}