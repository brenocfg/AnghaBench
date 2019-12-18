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
struct regmap {int dummy; } ;
struct qt1050_priv {struct input_dev* input; struct regmap* regmap; int /*<<< orphan*/ * keycodes; TYPE_3__* keys; struct i2c_client* client; } ;
struct TYPE_6__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_5__ {struct device* parent; } ;
struct input_dev {char* name; int keycodesize; unsigned int keycodemax; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/ * keycode; TYPE_2__ id; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; int /*<<< orphan*/  irq; TYPE_4__* adapter; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  keycode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  QT1050_DET_STATUS ; 
 unsigned int QT1050_MAX_KEYS ; 
 int /*<<< orphan*/  QT1050_RESET_TIME ; 
 int /*<<< orphan*/  QT1050_RES_CAL ; 
 int QT1050_RES_CAL_CALIBRATE ; 
 int QT1050_RES_CAL_RESET ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dev_driver_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 struct qt1050_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct qt1050_priv*) ; 
 int i2c_check_functionality (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct qt1050_priv*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int qt1050_apply_fw_data (struct qt1050_priv*) ; 
 int /*<<< orphan*/  qt1050_identify (struct qt1050_priv*) ; 
 int /*<<< orphan*/  qt1050_irq_threaded ; 
 int qt1050_parse_fw (struct qt1050_priv*) ; 
 int /*<<< orphan*/  qt1050_regmap_config ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_read_poll_timeout (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qt1050_probe(struct i2c_client *client)
{
	struct qt1050_priv *ts;
	struct input_dev *input;
	struct device *dev = &client->dev;
	struct regmap *map;
	unsigned int status, i;
	int err;

	/* Check basic functionality */
	err = i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE);
	if (!err) {
		dev_err(&client->dev, "%s adapter not supported\n",
			dev_driver_string(&client->adapter->dev));
		return -ENODEV;
	}

	if (!client->irq) {
		dev_err(dev, "assign a irq line to this device\n");
		return -EINVAL;
	}

	ts = devm_kzalloc(dev, sizeof(*ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	input = devm_input_allocate_device(dev);
	if (!input)
		return -ENOMEM;

	map = devm_regmap_init_i2c(client, &qt1050_regmap_config);
	if (IS_ERR(map))
		return PTR_ERR(map);

	ts->client = client;
	ts->input = input;
	ts->regmap = map;

	i2c_set_clientdata(client, ts);

	/* Identify the qt1050 chip */
	if (!qt1050_identify(ts))
		return -ENODEV;

	/* Get pdata */
	err = qt1050_parse_fw(ts);
	if (err) {
		dev_err(dev, "Failed to parse firmware: %d\n", err);
		return err;
	}

	input->name = "AT42QT1050 QTouch Sensor";
	input->dev.parent = &client->dev;
	input->id.bustype = BUS_I2C;

	/* Add the keycode */
	input->keycode = ts->keycodes;
	input->keycodesize = sizeof(ts->keycodes[0]);
	input->keycodemax = QT1050_MAX_KEYS;

	__set_bit(EV_KEY, input->evbit);
	for (i = 0; i < QT1050_MAX_KEYS; i++) {
		ts->keycodes[i] = ts->keys[i].keycode;
		__set_bit(ts->keycodes[i], input->keybit);
	}

	/* Trigger re-calibration */
	err = regmap_update_bits(ts->regmap, QT1050_RES_CAL, 0x7f,
				 QT1050_RES_CAL_CALIBRATE);
	if (err) {
		dev_err(dev, "Trigger calibration failed: %d\n", err);
		return err;
	}
	err = regmap_read_poll_timeout(ts->regmap, QT1050_DET_STATUS, status,
				 status >> 7 == 1, 10000, 200000);
	if (err) {
		dev_err(dev, "Calibration failed: %d\n", err);
		return err;
	}

	/* Soft reset to set defaults */
	err = regmap_update_bits(ts->regmap, QT1050_RES_CAL,
				 QT1050_RES_CAL_RESET, QT1050_RES_CAL_RESET);
	if (err) {
		dev_err(dev, "Trigger soft reset failed: %d\n", err);
		return err;
	}
	msleep(QT1050_RESET_TIME);

	/* Set pdata */
	err = qt1050_apply_fw_data(ts);
	if (err) {
		dev_err(dev, "Failed to set firmware data: %d\n", err);
		return err;
	}

	err = devm_request_threaded_irq(dev, client->irq, NULL,
					qt1050_irq_threaded, IRQF_ONESHOT,
					"qt1050", ts);
	if (err) {
		dev_err(&client->dev, "Failed to request irq: %d\n", err);
		return err;
	}

	/* Clear #CHANGE line */
	err = regmap_read(ts->regmap, QT1050_DET_STATUS, &status);
	if (err) {
		dev_err(dev, "Failed to clear #CHANGE line level: %d\n", err);
		return err;
	}

	/* Register the input device */
	err = input_register_device(ts->input);
	if (err) {
		dev_err(&client->dev, "Failed to register input device: %d\n",
			err);
		return err;
	}

	return 0;
}