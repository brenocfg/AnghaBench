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
struct i2c_client {int dummy; } ;
struct axp20x_dev {int dummy; } ;

/* Variables and functions */
 int axp20x_device_remove (struct axp20x_dev*) ; 
 struct axp20x_dev* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int axp20x_i2c_remove(struct i2c_client *i2c)
{
	struct axp20x_dev *axp20x = i2c_get_clientdata(i2c);

	return axp20x_device_remove(axp20x);
}