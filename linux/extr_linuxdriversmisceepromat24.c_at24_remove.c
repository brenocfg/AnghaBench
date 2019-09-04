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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct at24_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  at24_remove_dummy_clients (struct at24_data*) ; 
 struct at24_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at24_remove(struct i2c_client *client)
{
	struct at24_data *at24;

	at24 = i2c_get_clientdata(client);

	at24_remove_dummy_clients(at24);
	pm_runtime_disable(&client->dev);
	pm_runtime_set_suspended(&client->dev);

	return 0;
}