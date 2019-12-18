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
struct pc87427_data {int* address; int /*<<< orphan*/  lock; int /*<<< orphan*/ * fan_min; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_FM (int) ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  FAN_STATUS_MONEN ; 
 size_t LD_FAN ; 
 scalar_t__ PC87427_REG_BANK ; 
 scalar_t__ PC87427_REG_FAN_MIN ; 
 scalar_t__ PC87427_REG_FAN_STATUS ; 
 struct pc87427_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fan_to_reg (unsigned long) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_min_store(struct device *dev,
			     struct device_attribute *devattr,
			     const char *buf, size_t count)
{
	struct pc87427_data *data = dev_get_drvdata(dev);
	int nr = to_sensor_dev_attr(devattr)->index;
	unsigned long val;
	int iobase = data->address[LD_FAN];

	if (kstrtoul(buf, 10, &val) < 0)
		return -EINVAL;

	mutex_lock(&data->lock);
	outb(BANK_FM(nr), iobase + PC87427_REG_BANK);
	/*
	 * The low speed limit registers are read-only while monitoring
	 * is enabled, so we have to disable monitoring, then change the
	 * limit, and finally enable monitoring again.
	 */
	outb(0, iobase + PC87427_REG_FAN_STATUS);
	data->fan_min[nr] = fan_to_reg(val);
	outw(data->fan_min[nr], iobase + PC87427_REG_FAN_MIN);
	outb(FAN_STATUS_MONEN, iobase + PC87427_REG_FAN_STATUS);
	mutex_unlock(&data->lock);

	return count;
}