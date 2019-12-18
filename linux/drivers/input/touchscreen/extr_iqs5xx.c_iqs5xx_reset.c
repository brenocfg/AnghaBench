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
struct iqs5xx_private {int /*<<< orphan*/  reset_gpio; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct iqs5xx_private* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void iqs5xx_reset(struct i2c_client *client)
{
	struct iqs5xx_private *iqs5xx = i2c_get_clientdata(client);

	gpiod_set_value_cansleep(iqs5xx->reset_gpio, 1);
	usleep_range(200, 300);

	gpiod_set_value_cansleep(iqs5xx->reset_gpio, 0);
}