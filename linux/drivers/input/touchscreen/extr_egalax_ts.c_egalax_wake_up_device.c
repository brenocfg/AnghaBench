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
struct TYPE_2__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int gpio_request (int,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int egalax_wake_up_device(struct i2c_client *client)
{
	struct device_node *np = client->dev.of_node;
	int gpio;
	int ret;

	if (!np)
		return -ENODEV;

	gpio = of_get_named_gpio(np, "wakeup-gpios", 0);
	if (!gpio_is_valid(gpio))
		return -ENODEV;

	ret = gpio_request(gpio, "egalax_irq");
	if (ret < 0) {
		dev_err(&client->dev,
			"request gpio failed, cannot wake up controller: %d\n",
			ret);
		return ret;
	}

	/* wake up controller via an falling edge on IRQ gpio. */
	gpio_direction_output(gpio, 0);
	gpio_set_value(gpio, 1);

	/* controller should be waken up, return irq.  */
	gpio_direction_input(gpio);
	gpio_free(gpio);

	return 0;
}