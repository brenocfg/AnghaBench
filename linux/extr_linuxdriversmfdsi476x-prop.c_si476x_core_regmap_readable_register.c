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
typedef  int /*<<< orphan*/  u16 ;
struct si476x_core {int dummy; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct si476x_core* i2c_get_clientdata (struct i2c_client*) ; 
 int si476x_core_is_valid_property (struct si476x_core*,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static bool si476x_core_regmap_readable_register(struct device *dev,
						 unsigned int reg)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct si476x_core *core = i2c_get_clientdata(client);

	return si476x_core_is_valid_property(core, (u16) reg);

}