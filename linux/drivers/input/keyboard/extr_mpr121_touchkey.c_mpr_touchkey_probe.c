#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regulator {int dummy; } ;
struct mpr121_touchkey {int keycount; int /*<<< orphan*/ * keycodes; struct input_dev* input_dev; struct i2c_client* client; } ;
struct TYPE_5__ {struct device* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int keycodesize; int keycodemax; int /*<<< orphan*/ * keycode; int /*<<< orphan*/  evbit; TYPE_2__ dev; TYPE_1__ id; } ;
struct i2c_device_id {int dummy; } ;
struct device {TYPE_3__* driver; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int MPR121_MAX_KEY_COUNT ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int PTR_ERR (struct regulator*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,scalar_t__) ; 
 int device_property_count_u32 (struct device*,char*) ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 int device_property_read_u32_array (struct device*,char*,int /*<<< orphan*/ *,int) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 struct mpr121_touchkey* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mpr121_touchkey*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct mpr121_touchkey*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mpr121_phys_init (struct mpr121_touchkey*,struct i2c_client*,int) ; 
 struct regulator* mpr121_vdd_supply_init (struct device*) ; 
 int /*<<< orphan*/  mpr_touchkey_interrupt ; 
 int regulator_get_voltage (struct regulator*) ; 

__attribute__((used)) static int mpr_touchkey_probe(struct i2c_client *client,
			      const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct regulator *vdd_supply;
	int vdd_uv;
	struct mpr121_touchkey *mpr121;
	struct input_dev *input_dev;
	int error;
	int i;

	if (!client->irq) {
		dev_err(dev, "irq number should not be zero\n");
		return -EINVAL;
	}

	vdd_supply = mpr121_vdd_supply_init(dev);
	if (IS_ERR(vdd_supply))
		return PTR_ERR(vdd_supply);

	vdd_uv = regulator_get_voltage(vdd_supply);

	mpr121 = devm_kzalloc(dev, sizeof(*mpr121), GFP_KERNEL);
	if (!mpr121)
		return -ENOMEM;

	input_dev = devm_input_allocate_device(dev);
	if (!input_dev)
		return -ENOMEM;

	mpr121->client = client;
	mpr121->input_dev = input_dev;
	mpr121->keycount = device_property_count_u32(dev, "linux,keycodes");
	if (mpr121->keycount > MPR121_MAX_KEY_COUNT) {
		dev_err(dev, "too many keys defined (%d)\n", mpr121->keycount);
		return -EINVAL;
	}

	error = device_property_read_u32_array(dev, "linux,keycodes",
					       mpr121->keycodes,
					       mpr121->keycount);
	if (error) {
		dev_err(dev,
			"failed to read linux,keycode property: %d\n", error);
		return error;
	}

	input_dev->name = "Freescale MPR121 Touchkey";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = dev;
	if (device_property_read_bool(dev, "autorepeat"))
		__set_bit(EV_REP, input_dev->evbit);
	input_set_capability(input_dev, EV_MSC, MSC_SCAN);

	input_dev->keycode = mpr121->keycodes;
	input_dev->keycodesize = sizeof(mpr121->keycodes[0]);
	input_dev->keycodemax = mpr121->keycount;

	for (i = 0; i < mpr121->keycount; i++)
		input_set_capability(input_dev, EV_KEY, mpr121->keycodes[i]);

	error = mpr121_phys_init(mpr121, client, vdd_uv);
	if (error) {
		dev_err(dev, "Failed to init register\n");
		return error;
	}

	error = devm_request_threaded_irq(dev, client->irq, NULL,
					  mpr_touchkey_interrupt,
					  IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					  dev->driver->name, mpr121);
	if (error) {
		dev_err(dev, "Failed to register interrupt\n");
		return error;
	}

	error = input_register_device(input_dev);
	if (error)
		return error;

	i2c_set_clientdata(client, mpr121);
	device_init_wakeup(dev,
			device_property_read_bool(dev, "wakeup-source"));

	return 0;
}