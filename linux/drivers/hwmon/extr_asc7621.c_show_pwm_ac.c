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
 size_t clamp_val (int,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* data ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* param ; 
 int /*<<< orphan*/  sprintf (char*,char*,int const) ; 

__attribute__((used)) static ssize_t show_pwm_ac(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	SETUP_SHOW_DATA_PARAM(dev, attr);
	u8 config, altbit, regval;
	static const u8 map[] = {
		0x01, 0x02, 0x04, 0x1f, 0x00, 0x06, 0x07, 0x10,
		0x08, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f
	};

	mutex_lock(&data->update_lock);
	config = (data->reg[param->msb[0]] >> param->shift[0]) & param->mask[0];
	altbit = (data->reg[param->msb[1]] >> param->shift[1]) & param->mask[1];
	regval = config | (altbit << 3);
	mutex_unlock(&data->update_lock);

	return sprintf(buf, "%u\n", map[clamp_val(regval, 0, 15)]);
}