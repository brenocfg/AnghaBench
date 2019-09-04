#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* exit ) () ;} ;
struct kxtj9_data {TYPE_2__ pdata; int /*<<< orphan*/  input_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {scalar_t__ irq; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct kxtj9_data*) ; 
 struct kxtj9_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kxtj9_data*) ; 
 int /*<<< orphan*/  kxtj9_attribute_group ; 
 int /*<<< orphan*/  kxtj9_teardown_polled_device (struct kxtj9_data*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kxtj9_remove(struct i2c_client *client)
{
	struct kxtj9_data *tj9 = i2c_get_clientdata(client);

	if (client->irq) {
		sysfs_remove_group(&client->dev.kobj, &kxtj9_attribute_group);
		free_irq(client->irq, tj9);
		input_unregister_device(tj9->input_dev);
	} else {
		kxtj9_teardown_polled_device(tj9);
	}

	if (tj9->pdata.exit)
		tj9->pdata.exit();

	kfree(tj9);

	return 0;
}