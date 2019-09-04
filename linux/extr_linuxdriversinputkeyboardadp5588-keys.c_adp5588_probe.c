#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct TYPE_11__ {int vendor; int product; unsigned int version; int /*<<< orphan*/  bustype; } ;
struct TYPE_10__ {TYPE_5__* parent; } ;
struct input_dev {char* phys; int keycodesize; int keycodemax; scalar_t__* keycode; int /*<<< orphan*/  swbit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  keybit; TYPE_3__ id; TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_13__ {TYPE_1__* driver; } ;
struct i2c_client {int /*<<< orphan*/  irq; TYPE_5__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; } ;
struct adp5588_kpad_platform_data {unsigned short rows; unsigned short cols; int keymapsize; int gpimapsize; scalar_t__ repeat; TYPE_4__* gpimap; int /*<<< orphan*/  keymap; } ;
struct adp5588_kpad {scalar_t__* keycode; int gpimapsize; int /*<<< orphan*/  work; TYPE_4__* gpimap; int /*<<< orphan*/  delay; struct input_dev* input; struct i2c_client* client; } ;
struct TYPE_12__ {unsigned short pin; scalar_t__ sw_evt; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ADP5588_DEVICE_ID_MASK ; 
 int ADP5588_GPIMAPSIZE_MAX ; 
 int ADP5588_KEYMAPSIZE ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int /*<<< orphan*/  DEV_ID ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ EV_KEY ; 
 scalar_t__ EV_REP ; 
 scalar_t__ EV_SW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned short GPI_PIN_BASE ; 
 unsigned short GPI_PIN_COL_BASE ; 
 unsigned short GPI_PIN_END ; 
 unsigned short GPI_PIN_ROW_BASE ; 
 unsigned short GPI_PIN_ROW_END ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 scalar_t__ KEY_MAX ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 scalar_t__ WA_DELAYED_READOUT_REVID (unsigned int) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int adp5588_gpio_add (struct adp5588_kpad*) ; 
 int /*<<< orphan*/  adp5588_irq ; 
 int adp5588_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adp5588_report_switch_state (struct adp5588_kpad*) ; 
 int adp5588_setup (struct i2c_client*) ; 
 int /*<<< orphan*/  adp5588_work ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 struct adp5588_kpad_platform_data* dev_get_platdata (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_5__*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adp5588_kpad*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adp5588_kpad*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct adp5588_kpad*) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct adp5588_kpad*) ; 
 struct adp5588_kpad* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adp5588_kpad*) ; 

__attribute__((used)) static int adp5588_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct adp5588_kpad *kpad;
	const struct adp5588_kpad_platform_data *pdata =
			dev_get_platdata(&client->dev);
	struct input_dev *input;
	unsigned int revid;
	int ret, i;
	int error;

	if (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev, "SMBUS Byte Data not Supported\n");
		return -EIO;
	}

	if (!pdata) {
		dev_err(&client->dev, "no platform data?\n");
		return -EINVAL;
	}

	if (!pdata->rows || !pdata->cols || !pdata->keymap) {
		dev_err(&client->dev, "no rows, cols or keymap from pdata\n");
		return -EINVAL;
	}

	if (pdata->keymapsize != ADP5588_KEYMAPSIZE) {
		dev_err(&client->dev, "invalid keymapsize\n");
		return -EINVAL;
	}

	if (!pdata->gpimap && pdata->gpimapsize) {
		dev_err(&client->dev, "invalid gpimap from pdata\n");
		return -EINVAL;
	}

	if (pdata->gpimapsize > ADP5588_GPIMAPSIZE_MAX) {
		dev_err(&client->dev, "invalid gpimapsize\n");
		return -EINVAL;
	}

	for (i = 0; i < pdata->gpimapsize; i++) {
		unsigned short pin = pdata->gpimap[i].pin;

		if (pin < GPI_PIN_BASE || pin > GPI_PIN_END) {
			dev_err(&client->dev, "invalid gpi pin data\n");
			return -EINVAL;
		}

		if (pin <= GPI_PIN_ROW_END) {
			if (pin - GPI_PIN_ROW_BASE + 1 <= pdata->rows) {
				dev_err(&client->dev, "invalid gpi row data\n");
				return -EINVAL;
			}
		} else {
			if (pin - GPI_PIN_COL_BASE + 1 <= pdata->cols) {
				dev_err(&client->dev, "invalid gpi col data\n");
				return -EINVAL;
			}
		}
	}

	if (!client->irq) {
		dev_err(&client->dev, "no IRQ?\n");
		return -EINVAL;
	}

	kpad = kzalloc(sizeof(*kpad), GFP_KERNEL);
	input = input_allocate_device();
	if (!kpad || !input) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	kpad->client = client;
	kpad->input = input;
	INIT_DELAYED_WORK(&kpad->work, adp5588_work);

	ret = adp5588_read(client, DEV_ID);
	if (ret < 0) {
		error = ret;
		goto err_free_mem;
	}

	revid = (u8) ret & ADP5588_DEVICE_ID_MASK;
	if (WA_DELAYED_READOUT_REVID(revid))
		kpad->delay = msecs_to_jiffies(30);

	input->name = client->name;
	input->phys = "adp5588-keys/input0";
	input->dev.parent = &client->dev;

	input_set_drvdata(input, kpad);

	input->id.bustype = BUS_I2C;
	input->id.vendor = 0x0001;
	input->id.product = 0x0001;
	input->id.version = revid;

	input->keycodesize = sizeof(kpad->keycode[0]);
	input->keycodemax = pdata->keymapsize;
	input->keycode = kpad->keycode;

	memcpy(kpad->keycode, pdata->keymap,
		pdata->keymapsize * input->keycodesize);

	kpad->gpimap = pdata->gpimap;
	kpad->gpimapsize = pdata->gpimapsize;

	/* setup input device */
	__set_bit(EV_KEY, input->evbit);

	if (pdata->repeat)
		__set_bit(EV_REP, input->evbit);

	for (i = 0; i < input->keycodemax; i++)
		if (kpad->keycode[i] <= KEY_MAX)
			__set_bit(kpad->keycode[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);

	if (kpad->gpimapsize)
		__set_bit(EV_SW, input->evbit);
	for (i = 0; i < kpad->gpimapsize; i++)
		__set_bit(kpad->gpimap[i].sw_evt, input->swbit);

	error = input_register_device(input);
	if (error) {
		dev_err(&client->dev, "unable to register input device\n");
		goto err_free_mem;
	}

	error = request_irq(client->irq, adp5588_irq,
			    IRQF_TRIGGER_FALLING,
			    client->dev.driver->name, kpad);
	if (error) {
		dev_err(&client->dev, "irq %d busy?\n", client->irq);
		goto err_unreg_dev;
	}

	error = adp5588_setup(client);
	if (error)
		goto err_free_irq;

	if (kpad->gpimapsize)
		adp5588_report_switch_state(kpad);

	error = adp5588_gpio_add(kpad);
	if (error)
		goto err_free_irq;

	device_init_wakeup(&client->dev, 1);
	i2c_set_clientdata(client, kpad);

	dev_info(&client->dev, "Rev.%d keypad, irq %d\n", revid, client->irq);
	return 0;

 err_free_irq:
	free_irq(client->irq, kpad);
	cancel_delayed_work_sync(&kpad->work);
 err_unreg_dev:
	input_unregister_device(input);
	input = NULL;
 err_free_mem:
	input_free_device(input);
	kfree(kpad);

	return error;
}