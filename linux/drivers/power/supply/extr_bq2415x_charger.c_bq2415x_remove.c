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
struct i2c_client {int dummy; } ;
struct TYPE_2__ {scalar_t__ notifier_call; } ;
struct bq2415x_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  notify_node; TYPE_1__ nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  bq2415x_id ; 
 int /*<<< orphan*/  bq2415x_id_mutex ; 
 int /*<<< orphan*/  bq2415x_power_supply_exit (struct bq2415x_device*) ; 
 int /*<<< orphan*/  bq2415x_reset_chip (struct bq2415x_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct bq2415x_device* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_unreg_notifier (TYPE_1__*) ; 

__attribute__((used)) static int bq2415x_remove(struct i2c_client *client)
{
	struct bq2415x_device *bq = i2c_get_clientdata(client);

	if (bq->nb.notifier_call)
		power_supply_unreg_notifier(&bq->nb);

	of_node_put(bq->notify_node);
	bq2415x_power_supply_exit(bq);

	bq2415x_reset_chip(bq);

	mutex_lock(&bq2415x_id_mutex);
	idr_remove(&bq2415x_id, bq->id);
	mutex_unlock(&bq2415x_id_mutex);

	dev_info(bq->dev, "driver unregistered\n");

	kfree(bq->name);

	return 0;
}