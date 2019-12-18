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
struct ltc294x_info {int /*<<< orphan*/  supply; int /*<<< orphan*/  work; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 struct ltc294x_info* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc294x_i2c_remove(struct i2c_client *client)
{
	struct ltc294x_info *info = i2c_get_clientdata(client);

	cancel_delayed_work(&info->work);
	power_supply_unregister(info->supply);
	return 0;
}