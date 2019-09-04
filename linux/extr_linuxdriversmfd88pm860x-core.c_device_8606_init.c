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
struct pm860x_platform_data {int dummy; } ;
struct pm860x_chip {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_bk_init (struct pm860x_chip*,struct pm860x_platform_data*) ; 
 int /*<<< orphan*/  device_led_init (struct pm860x_chip*,struct pm860x_platform_data*) ; 
 int /*<<< orphan*/  device_osc_init (struct i2c_client*) ; 

__attribute__((used)) static void device_8606_init(struct pm860x_chip *chip,
				       struct i2c_client *i2c,
				       struct pm860x_platform_data *pdata)
{
	device_osc_init(i2c);
	device_bk_init(chip, pdata);
	device_led_init(chip, pdata);
}