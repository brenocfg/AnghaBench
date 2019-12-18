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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int* reg; int /*<<< orphan*/  update_lock; } ;
struct TYPE_3__ {size_t* msb; int* shift; int* mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETUP_SHOW_DATA_PARAM (struct device*,struct device_attribute*) ; 
 TYPE_2__* data ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* param ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_pwm_enable(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 config, altbit, minoff, val, newval;

	mutex_lock(&data->update_lock);
	config = (data->reg[param->msb[0]] >> param->shift[0]) & param->mask[0];
	altbit = (data->reg[param->msb[1]] >> param->shift[1]) & param->mask[1];
	minoff = (data->reg[param->msb[2]] >> param->shift[2]) & param->mask[2];
	mutex_unlock(&data->update_lock);

	val = config | (altbit << 3);

	if (val == 3 || val >= 10)
		newval = 255;
	else if (val == 4)
		newval = 0;
	else if (val == 7)
		newval = 1;
	else if (minoff == 1)
		newval = 2;
	else
		newval = 3;

	return sprintf(buf, "%u\n", newval);
}