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
struct aat2870_data {int /*<<< orphan*/  (* uninit ) (struct aat2870_data*) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  aat2870_disable (struct aat2870_data*) ; 
 int /*<<< orphan*/  aat2870_uninit_debugfs (struct aat2870_data*) ; 
 struct aat2870_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct aat2870_data*) ; 

__attribute__((used)) static int aat2870_i2c_remove(struct i2c_client *client)
{
	struct aat2870_data *aat2870 = i2c_get_clientdata(client);

	aat2870_uninit_debugfs(aat2870);

	mfd_remove_devices(aat2870->dev);
	aat2870_disable(aat2870);
	if (aat2870->uninit)
		aat2870->uninit(aat2870);

	return 0;
}