#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct elan_tp_data {TYPE_1__* ops; int /*<<< orphan*/  mode; struct i2c_client* client; } ;
struct TYPE_2__ {int (* initialize ) (struct i2c_client*) ;int (* sleep_control ) (struct i2c_client*,int) ;int (* set_mode ) (struct i2c_client*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_ENABLE_ABS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ elan_check_ASUS_special_fw (struct elan_tp_data*) ; 
 int elan_query_product (struct elan_tp_data*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct i2c_client*) ; 
 int stub2 (struct i2c_client*,int) ; 
 int stub3 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int stub4 (struct i2c_client*,int) ; 

__attribute__((used)) static int __elan_initialize(struct elan_tp_data *data)
{
	struct i2c_client *client = data->client;
	bool woken_up = false;
	int error;

	error = data->ops->initialize(client);
	if (error) {
		dev_err(&client->dev, "device initialize failed: %d\n", error);
		return error;
	}

	error = elan_query_product(data);
	if (error)
		return error;

	/*
	 * Some ASUS devices were shipped with firmware that requires
	 * touchpads to be woken up first, before attempting to switch
	 * them into absolute reporting mode.
	 */
	if (elan_check_ASUS_special_fw(data)) {
		error = data->ops->sleep_control(client, false);
		if (error) {
			dev_err(&client->dev,
				"failed to wake device up: %d\n", error);
			return error;
		}

		msleep(200);
		woken_up = true;
	}

	data->mode |= ETP_ENABLE_ABS;
	error = data->ops->set_mode(client, data->mode);
	if (error) {
		dev_err(&client->dev,
			"failed to switch to absolute mode: %d\n", error);
		return error;
	}

	if (!woken_up) {
		error = data->ops->sleep_control(client, false);
		if (error) {
			dev_err(&client->dev,
				"failed to wake device up: %d\n", error);
			return error;
		}
	}

	return 0;
}