#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tca6416_keys_platform_data {int nbuttons; scalar_t__ irq_is_gpio; TYPE_3__* buttons; scalar_t__ rep; int /*<<< orphan*/  use_polling; int /*<<< orphan*/  pinmask; } ;
struct tca6416_keypad_chip {int /*<<< orphan*/  irqnum; int /*<<< orphan*/  use_polling; TYPE_3__* buttons; int /*<<< orphan*/  dwork; int /*<<< orphan*/  pinmask; int /*<<< orphan*/  io_size; struct input_dev* input; struct i2c_client* client; } ;
struct TYPE_6__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {char* phys; int /*<<< orphan*/  evbit; TYPE_2__ id; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; TYPE_4__* adapter; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int type; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 unsigned int EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buttons ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_driver_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct tca6416_keys_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tca6416_keypad_chip*) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tca6416_keypad_chip*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct tca6416_keypad_chip*) ; 
 int /*<<< orphan*/  kfree (struct tca6416_keypad_chip*) ; 
 struct tca6416_keypad_chip* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct tca6416_keypad_chip*) ; 
 int /*<<< orphan*/  struct_size (struct tca6416_keypad_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tca6416_keys_close ; 
 int /*<<< orphan*/  tca6416_keys_isr ; 
 int /*<<< orphan*/  tca6416_keys_open ; 
 int /*<<< orphan*/  tca6416_keys_work_func ; 
 int tca6416_setup_registers (struct tca6416_keypad_chip*) ; 

__attribute__((used)) static int tca6416_keypad_probe(struct i2c_client *client,
				   const struct i2c_device_id *id)
{
	struct tca6416_keys_platform_data *pdata;
	struct tca6416_keypad_chip *chip;
	struct input_dev *input;
	int error;
	int i;

	/* Check functionality */
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE)) {
		dev_err(&client->dev, "%s adapter not supported\n",
			dev_driver_string(&client->adapter->dev));
		return -ENODEV;
	}

	pdata = dev_get_platdata(&client->dev);
	if (!pdata) {
		dev_dbg(&client->dev, "no platform data\n");
		return -EINVAL;
	}

	chip = kzalloc(struct_size(chip, buttons, pdata->nbuttons), GFP_KERNEL);
	input = input_allocate_device();
	if (!chip || !input) {
		error = -ENOMEM;
		goto fail1;
	}

	chip->client = client;
	chip->input = input;
	chip->io_size = id->driver_data;
	chip->pinmask = pdata->pinmask;
	chip->use_polling = pdata->use_polling;

	INIT_DELAYED_WORK(&chip->dwork, tca6416_keys_work_func);

	input->phys = "tca6416-keys/input0";
	input->name = client->name;
	input->dev.parent = &client->dev;

	input->open = tca6416_keys_open;
	input->close = tca6416_keys_close;

	input->id.bustype = BUS_HOST;
	input->id.vendor = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	/* Enable auto repeat feature of Linux input subsystem */
	if (pdata->rep)
		__set_bit(EV_REP, input->evbit);

	for (i = 0; i < pdata->nbuttons; i++) {
		unsigned int type;

		chip->buttons[i] = pdata->buttons[i];
		type = (pdata->buttons[i].type) ?: EV_KEY;
		input_set_capability(input, type, pdata->buttons[i].code);
	}

	input_set_drvdata(input, chip);

	/*
	 * Initialize cached registers from their original values.
	 * we can't share this chip with another i2c master.
	 */
	error = tca6416_setup_registers(chip);
	if (error)
		goto fail1;

	if (!chip->use_polling) {
		if (pdata->irq_is_gpio)
			chip->irqnum = gpio_to_irq(client->irq);
		else
			chip->irqnum = client->irq;

		error = request_threaded_irq(chip->irqnum, NULL,
					     tca6416_keys_isr,
					     IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
					     "tca6416-keypad", chip);
		if (error) {
			dev_dbg(&client->dev,
				"Unable to claim irq %d; error %d\n",
				chip->irqnum, error);
			goto fail1;
		}
		disable_irq(chip->irqnum);
	}

	error = input_register_device(input);
	if (error) {
		dev_dbg(&client->dev,
			"Unable to register input device, error: %d\n", error);
		goto fail2;
	}

	i2c_set_clientdata(client, chip);
	device_init_wakeup(&client->dev, 1);

	return 0;

fail2:
	if (!chip->use_polling) {
		free_irq(chip->irqnum, chip);
		enable_irq(chip->irqnum);
	}
fail1:
	input_free_device(input);
	kfree(chip);
	return error;
}