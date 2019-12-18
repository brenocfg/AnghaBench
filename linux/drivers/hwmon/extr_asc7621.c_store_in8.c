#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_6__ {long* reg; int /*<<< orphan*/  update_lock; } ;
struct TYPE_5__ {size_t* msb; } ;
struct TYPE_4__ {size_t index; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  SETUP_STORE_DATA_PARAM (struct device*,struct device_attribute*) ; 
 long* asc7621_in_scaling ; 
 long clamp_val (long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  client ; 
 TYPE_3__* data ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* param ; 
 TYPE_1__* sda ; 
 int /*<<< orphan*/  write_byte (int /*<<< orphan*/ ,size_t,long) ; 

__attribute__((used)) static ssize_t store_in8(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	SETUP_STORE_DATA_PARAM(dev, attr);
	long reqval;
	u8 nr = sda->index;

	if (kstrtol(buf, 10, &reqval))
		return -EINVAL;

	reqval = clamp_val(reqval, 0, 0xffff);

	reqval = reqval * 0xc0 / asc7621_in_scaling[nr];

	reqval = clamp_val(reqval, 0, 0xff);

	mutex_lock(&data->update_lock);
	data->reg[param->msb[0]] = reqval;
	write_byte(client, param->msb[0], reqval);
	mutex_unlock(&data->update_lock);

	return count;
}