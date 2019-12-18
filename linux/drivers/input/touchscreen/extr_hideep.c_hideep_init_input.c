#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ max_x; scalar_t__ max_y; } ;
struct hideep_ts {int key_num; TYPE_3__* input_dev; int /*<<< orphan*/ * key_codes; TYPE_4__ prop; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_13__ {int keycodesize; int keycodemax; int /*<<< orphan*/ * keycode; TYPE_2__ id; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOOL_TYPE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int HIDEEP_KEY_MAX ; 
 int /*<<< orphan*/  HIDEEP_MT_MAX ; 
 int /*<<< orphan*/  HIDEEP_TS_NAME ; 
 int /*<<< orphan*/  INPUT_MT_DIRECT ; 
 int MT_TOOL_MAX ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int device_property_count_u32 (struct device*,char*) ; 
 int device_property_read_u32_array (struct device*,char*,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* devm_input_allocate_device (struct device*) ; 
 int hideep_get_axis_info (struct hideep_ts*) ; 
 int input_mt_init_slots (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_3__*) ; 
 int /*<<< orphan*/  input_set_abs_params (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_3__*,struct hideep_ts*) ; 
 int /*<<< orphan*/  touchscreen_parse_properties (TYPE_3__*,int,TYPE_4__*) ; 

__attribute__((used)) static int hideep_init_input(struct hideep_ts *ts)
{
	struct device *dev = &ts->client->dev;
	int i;
	int error;

	ts->input_dev = devm_input_allocate_device(dev);
	if (!ts->input_dev) {
		dev_err(dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	ts->input_dev->name = HIDEEP_TS_NAME;
	ts->input_dev->id.bustype = BUS_I2C;
	input_set_drvdata(ts->input_dev, ts);

	input_set_capability(ts->input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(ts->input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_abs_params(ts->input_dev, ABS_MT_PRESSURE, 0, 65535, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_TOOL_TYPE,
			     0, MT_TOOL_MAX, 0, 0);
	touchscreen_parse_properties(ts->input_dev, true, &ts->prop);

	if (ts->prop.max_x == 0 || ts->prop.max_y == 0) {
		error = hideep_get_axis_info(ts);
		if (error)
			return error;
	}

	error = input_mt_init_slots(ts->input_dev, HIDEEP_MT_MAX,
				    INPUT_MT_DIRECT);
	if (error)
		return error;

	ts->key_num = device_property_count_u32(dev, "linux,keycodes");
	if (ts->key_num > HIDEEP_KEY_MAX) {
		dev_err(dev, "too many keys defined: %d\n",
			ts->key_num);
		return -EINVAL;
	}

	if (ts->key_num <= 0) {
		dev_dbg(dev,
			"missing or malformed 'linux,keycodes' property\n");
	} else {
		error = device_property_read_u32_array(dev, "linux,keycodes",
						       ts->key_codes,
						       ts->key_num);
		if (error) {
			dev_dbg(dev, "failed to read keymap: %d", error);
			return error;
		}

		if (ts->key_num) {
			ts->input_dev->keycode = ts->key_codes;
			ts->input_dev->keycodesize = sizeof(ts->key_codes[0]);
			ts->input_dev->keycodemax = ts->key_num;

			for (i = 0; i < ts->key_num; i++)
				input_set_capability(ts->input_dev, EV_KEY,
					ts->key_codes[i]);
		}
	}

	error = input_register_device(ts->input_dev);
	if (error) {
		dev_err(dev, "failed to register input device: %d", error);
		return error;
	}

	return 0;
}