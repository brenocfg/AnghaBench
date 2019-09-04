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
struct as5011_device {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  button_gpio; int /*<<< orphan*/  button_irq; int /*<<< orphan*/  axis_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct as5011_device*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 struct as5011_device* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct as5011_device*) ; 

__attribute__((used)) static int as5011_remove(struct i2c_client *client)
{
	struct as5011_device *as5011 = i2c_get_clientdata(client);

	free_irq(as5011->axis_irq, as5011);
	free_irq(as5011->button_irq, as5011);
	gpio_free(as5011->button_gpio);

	input_unregister_device(as5011->input_dev);
	kfree(as5011);

	return 0;
}