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
struct apds990x_chip {int /*<<< orphan*/  regs; TYPE_2__* pdata; TYPE_1__* client; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* release_resources ) () ;} ;
struct TYPE_4__ {TYPE_3__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apds990x_attribute_group ; 
 int /*<<< orphan*/  apds990x_chip_off (struct apds990x_chip*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct apds990x_chip*) ; 
 struct apds990x_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct apds990x_chip*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apds990x_remove(struct i2c_client *client)
{
	struct apds990x_chip *chip = i2c_get_clientdata(client);

	free_irq(client->irq, chip);
	sysfs_remove_group(&chip->client->dev.kobj,
			apds990x_attribute_group);

	if (chip->pdata && chip->pdata->release_resources)
		chip->pdata->release_resources();

	if (!pm_runtime_suspended(&client->dev))
		apds990x_chip_off(chip);

	pm_runtime_disable(&client->dev);
	pm_runtime_set_suspended(&client->dev);

	regulator_bulk_free(ARRAY_SIZE(chip->regs), chip->regs);

	kfree(chip);
	return 0;
}