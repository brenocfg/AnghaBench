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
struct i2c_client {int dummy; } ;
struct bu21013_ts_data {int /*<<< orphan*/  regulator; int /*<<< orphan*/  in_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bu21013_cs_disable (struct bu21013_ts_data*) ; 
 int /*<<< orphan*/  bu21013_free_irq (struct bu21013_ts_data*) ; 
 struct bu21013_ts_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bu21013_ts_data*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bu21013_remove(struct i2c_client *client)
{
	struct bu21013_ts_data *bu21013_data = i2c_get_clientdata(client);

	bu21013_free_irq(bu21013_data);

	bu21013_cs_disable(bu21013_data);

	input_unregister_device(bu21013_data->in_dev);

	regulator_disable(bu21013_data->regulator);
	regulator_put(bu21013_data->regulator);

	kfree(bu21013_data);

	return 0;
}