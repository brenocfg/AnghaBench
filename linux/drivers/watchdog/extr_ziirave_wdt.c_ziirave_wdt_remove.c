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
struct ziirave_wdt_data {int /*<<< orphan*/  wdd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct ziirave_wdt_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ziirave_wdt_remove(struct i2c_client *client)
{
	struct ziirave_wdt_data *w_priv = i2c_get_clientdata(client);

	watchdog_unregister_device(&w_priv->wdd);

	return 0;
}