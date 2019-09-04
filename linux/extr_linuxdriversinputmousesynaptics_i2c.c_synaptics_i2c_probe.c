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
struct synaptics_i2c {int /*<<< orphan*/  input; TYPE_1__* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int irq; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INTERRUPT_EN_REG ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_FALLING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct synaptics_i2c*) ; 
 int /*<<< orphan*/  input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ ) ; 
 int input_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct synaptics_i2c*) ; 
 int polling_req ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct synaptics_i2c*) ; 
 int /*<<< orphan*/  scan_rate ; 
 int /*<<< orphan*/  synaptics_i2c_irq ; 
 int /*<<< orphan*/  synaptics_i2c_reg_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int synaptics_i2c_reset_config (struct i2c_client*) ; 
 int /*<<< orphan*/  synaptics_i2c_set_input_params (struct synaptics_i2c*) ; 
 struct synaptics_i2c* synaptics_i2c_touch_create (struct i2c_client*) ; 

__attribute__((used)) static int synaptics_i2c_probe(struct i2c_client *client,
			       const struct i2c_device_id *dev_id)
{
	int ret;
	struct synaptics_i2c *touch;

	touch = synaptics_i2c_touch_create(client);
	if (!touch)
		return -ENOMEM;

	ret = synaptics_i2c_reset_config(client);
	if (ret)
		goto err_mem_free;

	if (client->irq < 1)
		polling_req = true;

	touch->input = input_allocate_device();
	if (!touch->input) {
		ret = -ENOMEM;
		goto err_mem_free;
	}

	synaptics_i2c_set_input_params(touch);

	if (!polling_req) {
		dev_dbg(&touch->client->dev,
			 "Requesting IRQ: %d\n", touch->client->irq);

		ret = request_irq(touch->client->irq, synaptics_i2c_irq,
				  IRQ_TYPE_EDGE_FALLING,
				  DRIVER_NAME, touch);
		if (ret) {
			dev_warn(&touch->client->dev,
				  "IRQ request failed: %d, "
				  "falling back to polling\n", ret);
			polling_req = true;
			synaptics_i2c_reg_set(touch->client,
					      INTERRUPT_EN_REG, 0);
		}
	}

	if (polling_req)
		dev_dbg(&touch->client->dev,
			 "Using polling at rate: %d times/sec\n", scan_rate);

	/* Register the device in input subsystem */
	ret = input_register_device(touch->input);
	if (ret) {
		dev_err(&client->dev,
			 "Input device register failed: %d\n", ret);
		goto err_input_free;
	}

	i2c_set_clientdata(client, touch);

	return 0;

err_input_free:
	input_free_device(touch->input);
err_mem_free:
	kfree(touch);

	return ret;
}