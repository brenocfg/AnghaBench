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
struct mcs_touchkey_data {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  (* poweron ) (int) ;} ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mcs_touchkey_data*) ; 
 struct mcs_touchkey_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mcs_touchkey_data*) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static int mcs_touchkey_remove(struct i2c_client *client)
{
	struct mcs_touchkey_data *data = i2c_get_clientdata(client);

	free_irq(client->irq, data);
	if (data->poweron)
		data->poweron(false);
	input_unregister_device(data->input_dev);
	kfree(data);

	return 0;
}