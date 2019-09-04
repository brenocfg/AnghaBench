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
struct sm501_platdata_gpio_i2c {int dummy; } ;
struct sm501_platdata {int gpio_i2c_nr; struct sm501_platdata_gpio_i2c* gpio_i2c; } ;
struct sm501_devdata {int dummy; } ;

/* Variables and functions */
 int sm501_register_gpio_i2c_instance (struct sm501_devdata*,struct sm501_platdata_gpio_i2c*) ; 

__attribute__((used)) static int sm501_register_gpio_i2c(struct sm501_devdata *sm,
				   struct sm501_platdata *pdata)
{
	struct sm501_platdata_gpio_i2c *iic = pdata->gpio_i2c;
	int index;
	int ret;

	for (index = 0; index < pdata->gpio_i2c_nr; index++, iic++) {
		ret = sm501_register_gpio_i2c_instance(sm, iic);
		if (ret < 0)
			return ret;
	}

	return 0;
}