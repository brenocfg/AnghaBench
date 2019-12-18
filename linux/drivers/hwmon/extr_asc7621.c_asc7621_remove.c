#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct asc7621_data {int /*<<< orphan*/  class_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_5__ {TYPE_1__ sda; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 TYPE_2__* asc7621_params ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct asc7621_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int asc7621_remove(struct i2c_client *client)
{
	struct asc7621_data *data = i2c_get_clientdata(client);
	int i;

	hwmon_device_unregister(data->class_dev);

	for (i = 0; i < ARRAY_SIZE(asc7621_params); i++) {
		device_remove_file(&client->dev,
				   &(asc7621_params[i].sda.dev_attr));
	}

	return 0;
}