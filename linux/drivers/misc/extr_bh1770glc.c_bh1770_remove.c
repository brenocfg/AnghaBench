#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct bh1770_chip {int /*<<< orphan*/  prox_work; TYPE_1__* pdata; TYPE_3__* client; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* release_resources ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bh1770_attribute_group ; 
 int /*<<< orphan*/  bh1770_chip_off (struct bh1770_chip*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bh1770_chip*) ; 
 struct bh1770_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bh1770_remove(struct i2c_client *client)
{
	struct bh1770_chip *chip = i2c_get_clientdata(client);

	free_irq(client->irq, chip);

	sysfs_remove_group(&chip->client->dev.kobj,
			&bh1770_attribute_group);

	if (chip->pdata->release_resources)
		chip->pdata->release_resources();

	cancel_delayed_work_sync(&chip->prox_work);

	if (!pm_runtime_suspended(&client->dev))
		bh1770_chip_off(chip);

	pm_runtime_disable(&client->dev);
	pm_runtime_set_suspended(&client->dev);

	return 0;
}