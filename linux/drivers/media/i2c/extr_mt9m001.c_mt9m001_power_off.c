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
struct mt9m001 {int /*<<< orphan*/  clk; int /*<<< orphan*/  standby_gpio; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct mt9m001* to_mt9m001 (struct i2c_client*) ; 

__attribute__((used)) static int mt9m001_power_off(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct mt9m001 *mt9m001 = to_mt9m001(client);

	gpiod_set_value_cansleep(mt9m001->standby_gpio, 1);
	clk_disable_unprepare(mt9m001->clk);

	return 0;
}