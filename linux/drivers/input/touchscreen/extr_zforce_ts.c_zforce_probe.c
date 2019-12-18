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
struct zforce_ts_platdata {int x_max; int y_max; } ;
struct zforce_ts {int /*<<< orphan*/  command_done; int /*<<< orphan*/  command_waiting; struct input_dev* input; int /*<<< orphan*/  phys; struct i2c_client* client; struct zforce_ts_platdata const* pdata; int /*<<< orphan*/  command_mutex; int /*<<< orphan*/  access_mutex; struct zforce_ts_platdata const* reg_vdd; struct zforce_ts_platdata const* gpio_rst; struct zforce_ts_platdata const* gpio_int; } ;
struct TYPE_2__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; int /*<<< orphan*/  phys; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int /*<<< orphan*/  COMMAND_INITIALIZE ; 
 int /*<<< orphan*/  COMMAND_STATUS ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SYN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  INPUT_MT_DIRECT ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (struct zforce_ts_platdata const*) ; 
 int /*<<< orphan*/  NOTIFICATION_BOOTCOMPLETE ; 
 int PTR_ERR (struct zforce_ts_platdata const*) ; 
 int /*<<< orphan*/  WAIT_TIMEOUT ; 
 int ZFORCE_MAX_AREA ; 
 int /*<<< orphan*/  ZFORCE_REPORT_POINTS ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct zforce_ts_platdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 int devm_add_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct zforce_ts*) ; 
 void* devm_gpiod_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct zforce_ts* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct zforce_ts_platdata const* devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct zforce_ts*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct zforce_ts*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_mt_init_slots (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct zforce_ts*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (struct zforce_ts_platdata const*) ; 
 int regulator_enable (struct zforce_ts_platdata const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zforce_command_wait (struct zforce_ts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zforce_input_close ; 
 int /*<<< orphan*/  zforce_input_open ; 
 int /*<<< orphan*/  zforce_irq ; 
 int /*<<< orphan*/  zforce_irq_thread ; 
 struct zforce_ts_platdata* zforce_parse_dt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zforce_reset ; 
 int /*<<< orphan*/  zforce_reset_deassert (struct zforce_ts*) ; 
 int zforce_stop (struct zforce_ts*) ; 

__attribute__((used)) static int zforce_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	const struct zforce_ts_platdata *pdata = dev_get_platdata(&client->dev);
	struct zforce_ts *ts;
	struct input_dev *input_dev;
	int ret;

	if (!pdata) {
		pdata = zforce_parse_dt(&client->dev);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
	}

	ts = devm_kzalloc(&client->dev, sizeof(struct zforce_ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	ts->gpio_rst = devm_gpiod_get_optional(&client->dev, "reset",
					       GPIOD_OUT_HIGH);
	if (IS_ERR(ts->gpio_rst)) {
		ret = PTR_ERR(ts->gpio_rst);
		dev_err(&client->dev,
			"failed to request reset GPIO: %d\n", ret);
		return ret;
	}

	if (ts->gpio_rst) {
		ts->gpio_int = devm_gpiod_get_optional(&client->dev, "irq",
						       GPIOD_IN);
		if (IS_ERR(ts->gpio_int)) {
			ret = PTR_ERR(ts->gpio_int);
			dev_err(&client->dev,
				"failed to request interrupt GPIO: %d\n", ret);
			return ret;
		}
	} else {
		/*
		 * Deprecated GPIO handling for compatibility
		 * with legacy binding.
		 */

		/* INT GPIO */
		ts->gpio_int = devm_gpiod_get_index(&client->dev, NULL, 0,
						    GPIOD_IN);
		if (IS_ERR(ts->gpio_int)) {
			ret = PTR_ERR(ts->gpio_int);
			dev_err(&client->dev,
				"failed to request interrupt GPIO: %d\n", ret);
			return ret;
		}

		/* RST GPIO */
		ts->gpio_rst = devm_gpiod_get_index(&client->dev, NULL, 1,
					    GPIOD_OUT_HIGH);
		if (IS_ERR(ts->gpio_rst)) {
			ret = PTR_ERR(ts->gpio_rst);
			dev_err(&client->dev,
				"failed to request reset GPIO: %d\n", ret);
			return ret;
		}
	}

	ts->reg_vdd = devm_regulator_get_optional(&client->dev, "vdd");
	if (IS_ERR(ts->reg_vdd)) {
		ret = PTR_ERR(ts->reg_vdd);
		if (ret == -EPROBE_DEFER)
			return ret;
	} else {
		ret = regulator_enable(ts->reg_vdd);
		if (ret)
			return ret;

		/*
		 * according to datasheet add 100us grace time after regular
		 * regulator enable delay.
		 */
		udelay(100);
	}

	ret = devm_add_action(&client->dev, zforce_reset, ts);
	if (ret) {
		dev_err(&client->dev, "failed to register reset action, %d\n",
			ret);

		/* hereafter the regulator will be disabled by the action */
		if (!IS_ERR(ts->reg_vdd))
			regulator_disable(ts->reg_vdd);

		return ret;
	}

	snprintf(ts->phys, sizeof(ts->phys),
		 "%s/input0", dev_name(&client->dev));

	input_dev = devm_input_allocate_device(&client->dev);
	if (!input_dev) {
		dev_err(&client->dev, "could not allocate input device\n");
		return -ENOMEM;
	}

	mutex_init(&ts->access_mutex);
	mutex_init(&ts->command_mutex);

	ts->pdata = pdata;
	ts->client = client;
	ts->input = input_dev;

	input_dev->name = "Neonode zForce touchscreen";
	input_dev->phys = ts->phys;
	input_dev->id.bustype = BUS_I2C;

	input_dev->open = zforce_input_open;
	input_dev->close = zforce_input_close;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(EV_SYN, input_dev->evbit);
	__set_bit(EV_ABS, input_dev->evbit);

	/* For multi touch */
	input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0,
			     pdata->x_max, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0,
			     pdata->y_max, 0, 0);

	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0,
			     ZFORCE_MAX_AREA, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MINOR, 0,
			     ZFORCE_MAX_AREA, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_ORIENTATION, 0, 1, 0, 0);
	input_mt_init_slots(input_dev, ZFORCE_REPORT_POINTS, INPUT_MT_DIRECT);

	input_set_drvdata(ts->input, ts);

	init_completion(&ts->command_done);

	/*
	 * The zforce pulls the interrupt low when it has data ready.
	 * After it is triggered the isr thread runs until all the available
	 * packets have been read and the interrupt is high again.
	 * Therefore we can trigger the interrupt anytime it is low and do
	 * not need to limit it to the interrupt edge.
	 */
	ret = devm_request_threaded_irq(&client->dev, client->irq,
					zforce_irq, zforce_irq_thread,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					input_dev->name, ts);
	if (ret) {
		dev_err(&client->dev, "irq %d request failed\n", client->irq);
		return ret;
	}

	i2c_set_clientdata(client, ts);

	/* let the controller boot */
	zforce_reset_deassert(ts);

	ts->command_waiting = NOTIFICATION_BOOTCOMPLETE;
	if (wait_for_completion_timeout(&ts->command_done, WAIT_TIMEOUT) == 0)
		dev_warn(&client->dev, "bootcomplete timed out\n");

	/* need to start device to get version information */
	ret = zforce_command_wait(ts, COMMAND_INITIALIZE);
	if (ret) {
		dev_err(&client->dev, "unable to initialize, %d\n", ret);
		return ret;
	}

	/* this gets the firmware version among other information */
	ret = zforce_command_wait(ts, COMMAND_STATUS);
	if (ret < 0) {
		dev_err(&client->dev, "couldn't get status, %d\n", ret);
		zforce_stop(ts);
		return ret;
	}

	/* stop device and put it into sleep until it is opened */
	ret = zforce_stop(ts);
	if (ret < 0)
		return ret;

	device_set_wakeup_capable(&client->dev, true);

	ret = input_register_device(input_dev);
	if (ret) {
		dev_err(&client->dev, "could not register input device, %d\n",
			ret);
		return ret;
	}

	return 0;
}