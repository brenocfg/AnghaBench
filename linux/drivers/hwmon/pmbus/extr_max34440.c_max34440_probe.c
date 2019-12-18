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
struct max34440_data {scalar_t__ id; int /*<<< orphan*/  info; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct max34440_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * max34440_info ; 
 scalar_t__ max34451 ; 
 int max34451_set_supported_funcs (struct i2c_client*,struct max34440_data*) ; 
 int pmbus_do_probe (struct i2c_client*,struct i2c_device_id const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max34440_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct max34440_data *data;
	int rv;

	data = devm_kzalloc(&client->dev, sizeof(struct max34440_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	data->id = id->driver_data;
	data->info = max34440_info[id->driver_data];

	if (data->id == max34451) {
		rv = max34451_set_supported_funcs(client, data);
		if (rv)
			return rv;
	}

	return pmbus_do_probe(client, id, &data->info);
}