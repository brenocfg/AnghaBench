#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; TYPE_2__ dev; TYPE_1__ id; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct as5011_platform_data {int axis_irq; int axis_irqflags; int /*<<< orphan*/  button_gpio; } ;
struct as5011_device {int axis_irq; int button_irq; int /*<<< orphan*/  button_gpio; struct input_dev* input_dev; struct i2c_client* i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  AS5011_FLAT ; 
 int /*<<< orphan*/  AS5011_FUZZ ; 
 int /*<<< orphan*/  AS5011_MAX_AXIS ; 
 int /*<<< orphan*/  AS5011_MIN_AXIS ; 
 int /*<<< orphan*/  BTN_JOYSTICK ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_NOSTART ; 
 int I2C_FUNC_PROTOCOL_MANGLING ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  as5011_axis_interrupt ; 
 int /*<<< orphan*/  as5011_button_interrupt ; 
 int as5011_configure_chip (struct as5011_device*,struct as5011_platform_data const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct as5011_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct as5011_device*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct as5011_device*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct as5011_device*) ; 
 struct as5011_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct as5011_device*) ; 

__attribute__((used)) static int as5011_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	const struct as5011_platform_data *plat_data;
	struct as5011_device *as5011;
	struct input_dev *input_dev;
	int irq;
	int error;

	plat_data = dev_get_platdata(&client->dev);
	if (!plat_data)
		return -EINVAL;

	if (!plat_data->axis_irq) {
		dev_err(&client->dev, "No axis IRQ?\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_NOSTART |
				     I2C_FUNC_PROTOCOL_MANGLING)) {
		dev_err(&client->dev,
			"need i2c bus that supports protocol mangling\n");
		return -ENODEV;
	}

	as5011 = kmalloc(sizeof(struct as5011_device), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!as5011 || !input_dev) {
		dev_err(&client->dev,
			"Can't allocate memory for device structure\n");
		error = -ENOMEM;
		goto err_free_mem;
	}

	as5011->i2c_client = client;
	as5011->input_dev = input_dev;
	as5011->button_gpio = plat_data->button_gpio;
	as5011->axis_irq = plat_data->axis_irq;

	input_dev->name = "Austria Microsystem as5011 joystick";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;

	input_set_capability(input_dev, EV_KEY, BTN_JOYSTICK);

	input_set_abs_params(input_dev, ABS_X,
		AS5011_MIN_AXIS, AS5011_MAX_AXIS, AS5011_FUZZ, AS5011_FLAT);
	input_set_abs_params(as5011->input_dev, ABS_Y,
		AS5011_MIN_AXIS, AS5011_MAX_AXIS, AS5011_FUZZ, AS5011_FLAT);

	error = gpio_request(as5011->button_gpio, "AS5011 button");
	if (error < 0) {
		dev_err(&client->dev, "Failed to request button gpio\n");
		goto err_free_mem;
	}

	irq = gpio_to_irq(as5011->button_gpio);
	if (irq < 0) {
		dev_err(&client->dev,
			"Failed to get irq number for button gpio\n");
		error = irq;
		goto err_free_button_gpio;
	}

	as5011->button_irq = irq;

	error = request_threaded_irq(as5011->button_irq,
				     NULL, as5011_button_interrupt,
				     IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				     "as5011_button", as5011);
	if (error < 0) {
		dev_err(&client->dev,
			"Can't allocate button irq %d\n", as5011->button_irq);
		goto err_free_button_gpio;
	}

	error = as5011_configure_chip(as5011, plat_data);
	if (error)
		goto err_free_button_irq;

	error = request_threaded_irq(as5011->axis_irq, NULL,
				     as5011_axis_interrupt,
				     plat_data->axis_irqflags | IRQF_ONESHOT,
				     "as5011_joystick", as5011);
	if (error) {
		dev_err(&client->dev,
			"Can't allocate axis irq %d\n", plat_data->axis_irq);
		goto err_free_button_irq;
	}

	error = input_register_device(as5011->input_dev);
	if (error) {
		dev_err(&client->dev, "Failed to register input device\n");
		goto err_free_axis_irq;
	}

	i2c_set_clientdata(client, as5011);

	return 0;

err_free_axis_irq:
	free_irq(as5011->axis_irq, as5011);
err_free_button_irq:
	free_irq(as5011->button_irq, as5011);
err_free_button_gpio:
	gpio_free(as5011->button_gpio);
err_free_mem:
	input_free_device(input_dev);
	kfree(as5011);

	return error;
}