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
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct bma150_data {int /*<<< orphan*/  input_polled; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct bma150_data*) ; 
 struct bma150_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_free_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bma150_data*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bma150_remove(struct i2c_client *client)
{
	struct bma150_data *bma150 = i2c_get_clientdata(client);

	pm_runtime_disable(&client->dev);

	if (client->irq > 0) {
		free_irq(client->irq, bma150);
		input_unregister_device(bma150->input);
	} else {
		input_unregister_polled_device(bma150->input_polled);
		input_free_polled_device(bma150->input_polled);
	}

	kfree(bma150);

	return 0;
}