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
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct gp2a_platform_data {int /*<<< orphan*/  (* hw_shutdown ) (struct i2c_client*) ;int /*<<< orphan*/  vout_gpio; } ;
struct gp2a_data {int /*<<< orphan*/  input; struct gp2a_platform_data* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct gp2a_data*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 struct gp2a_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gp2a_data*) ; 
 int /*<<< orphan*/  stub1 (struct i2c_client*) ; 

__attribute__((used)) static int gp2a_remove(struct i2c_client *client)
{
	struct gp2a_data *dt = i2c_get_clientdata(client);
	const struct gp2a_platform_data *pdata = dt->pdata;

	free_irq(client->irq, dt);

	input_unregister_device(dt->input);
	kfree(dt);

	gpio_free(pdata->vout_gpio);

	if (pdata->hw_shutdown)
		pdata->hw_shutdown(client);

	return 0;
}