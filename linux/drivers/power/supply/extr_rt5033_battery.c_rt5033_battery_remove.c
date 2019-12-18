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
struct rt5033_battery {int /*<<< orphan*/  psy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct rt5033_battery* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5033_battery_remove(struct i2c_client *client)
{
	struct rt5033_battery *battery = i2c_get_clientdata(client);

	power_supply_unregister(battery->psy);

	return 0;
}