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
struct ina3221_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  pm_dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int INA3221_NUM_CHANNELS ; 
 struct ina3221_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ina3221_remove(struct i2c_client *client)
{
	struct ina3221_data *ina = dev_get_drvdata(&client->dev);
	int i;

	pm_runtime_disable(ina->pm_dev);
	pm_runtime_set_suspended(ina->pm_dev);

	/* pm_runtime_put_noidle() will decrease the PM refcount until 0 */
	for (i = 0; i < INA3221_NUM_CHANNELS; i++)
		pm_runtime_put_noidle(ina->pm_dev);

	mutex_destroy(&ina->lock);

	return 0;
}