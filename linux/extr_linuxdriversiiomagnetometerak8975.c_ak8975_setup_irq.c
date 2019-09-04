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
struct i2c_client {int irq; int /*<<< orphan*/  dev; } ;
struct ak8975_data {int eoc_irq; int /*<<< orphan*/  eoc_gpio; int /*<<< orphan*/  flags; int /*<<< orphan*/  data_ready_queue; struct i2c_client* client; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  ak8975_irq_handler ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ak8975_data*) ; 
 int gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ak8975_setup_irq(struct ak8975_data *data)
{
	struct i2c_client *client = data->client;
	int rc;
	int irq;

	init_waitqueue_head(&data->data_ready_queue);
	clear_bit(0, &data->flags);
	if (client->irq)
		irq = client->irq;
	else
		irq = gpio_to_irq(data->eoc_gpio);

	rc = devm_request_irq(&client->dev, irq, ak8975_irq_handler,
			      IRQF_TRIGGER_RISING | IRQF_ONESHOT,
			      dev_name(&client->dev), data);
	if (rc < 0) {
		dev_err(&client->dev,
			"irq %d request failed, (gpio %d): %d\n",
			irq, data->eoc_gpio, rc);
		return rc;
	}

	data->eoc_irq = irq;

	return rc;
}