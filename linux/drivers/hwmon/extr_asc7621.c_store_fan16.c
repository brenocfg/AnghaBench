#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {long* reg; int /*<<< orphan*/  update_lock; } ;
struct TYPE_3__ {size_t* msb; size_t* lsb; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  SETUP_STORE_DATA_PARAM (struct device*,struct device_attribute*) ; 
 int clamp_val (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  client ; 
 TYPE_2__* data ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* param ; 
 int /*<<< orphan*/  write_byte (int /*<<< orphan*/ ,size_t,long) ; 

__attribute__((used)) static ssize_t store_fan16(struct device *dev,
			   struct device_attribute *attr, const char *buf,
			   size_t count)
{
	SETUP_STORE_DATA_PARAM(dev, attr);
	long reqval;

	if (kstrtol(buf, 10, &reqval))
		return -EINVAL;

	/*
	 * If a minimum RPM of zero is requested, then we set the register to
	 * 0xffff. This value allows the fan to be stopped completely without
	 * generating an alarm.
	 */
	reqval =
	    (reqval <= 0 ? 0xffff : clamp_val(5400000 / reqval, 0, 0xfffe));

	mutex_lock(&data->update_lock);
	data->reg[param->msb[0]] = (reqval >> 8) & 0xff;
	data->reg[param->lsb[0]] = reqval & 0xff;
	write_byte(client, param->msb[0], data->reg[param->msb[0]]);
	write_byte(client, param->lsb[0], data->reg[param->lsb[0]]);
	mutex_unlock(&data->update_lock);

	return count;
}