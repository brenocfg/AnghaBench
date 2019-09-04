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
typedef  int u8 ;
typedef  int u16 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int* reg; int /*<<< orphan*/  update_lock; } ;
struct TYPE_3__ {int* mask; int* shift; size_t* msb; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  SETUP_STORE_DATA_PARAM (struct device*,struct device_attribute*) ; 
 int /*<<< orphan*/  client ; 
 TYPE_2__* data ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* param ; 
 int read_byte (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  write_byte (int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static ssize_t store_pwm_ac(struct device *dev,
			    struct device_attribute *attr,
			    const char *buf, size_t count)
{
	SETUP_STORE_DATA_PARAM(dev, attr);
	unsigned long reqval;
	u8 currval, config, altbit, newval;
	static const u16 map[] = {
		0x04, 0x00, 0x01, 0xff, 0x02, 0xff, 0x05, 0x06,
		0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f,
		0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
	};

	if (kstrtoul(buf, 10, &reqval))
		return -EINVAL;

	if (reqval > 31)
		return -EINVAL;

	reqval = map[reqval];
	if (reqval == 0xff)
		return -EINVAL;

	config = reqval & 0x07;
	altbit = (reqval >> 3) & 0x01;

	config = (config & param->mask[0]) << param->shift[0];
	altbit = (altbit & param->mask[1]) << param->shift[1];

	mutex_lock(&data->update_lock);
	currval = read_byte(client, param->msb[0]);
	newval = config | (currval & ~(param->mask[0] << param->shift[0]));
	newval = altbit | (newval & ~(param->mask[1] << param->shift[1]));
	data->reg[param->msb[0]] = newval;
	write_byte(client, param->msb[0], newval);
	mutex_unlock(&data->update_lock);
	return count;
}