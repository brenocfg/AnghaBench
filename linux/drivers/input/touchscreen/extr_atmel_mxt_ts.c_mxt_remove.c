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
struct mxt_data {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct mxt_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mxt_attr_group ; 
 int /*<<< orphan*/  mxt_free_input_device (struct mxt_data*) ; 
 int /*<<< orphan*/  mxt_free_object_table (struct mxt_data*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxt_remove(struct i2c_client *client)
{
	struct mxt_data *data = i2c_get_clientdata(client);

	disable_irq(data->irq);
	sysfs_remove_group(&client->dev.kobj, &mxt_attr_group);
	mxt_free_input_device(data);
	mxt_free_object_table(data);

	return 0;
}