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
typedef  int u8 ;
struct goodix_ts_data {int int_trigger_type; int max_touch_num; int /*<<< orphan*/  input_dev; TYPE_2__* client; TYPE_1__* chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  config_len; int /*<<< orphan*/  config_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int GOODIX_CONFIG_MAX_LENGTH ; 
 int GOODIX_INT_TRIGGER ; 
 int GOODIX_MAX_CONTACTS ; 
 size_t MAX_CONTACTS_LOC ; 
 size_t RESOLUTION_LOC ; 
 size_t TRIGGER_LOC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int get_unaligned_le16 (int*) ; 
 int goodix_i2c_read (TYPE_2__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_abs_set_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void goodix_read_config(struct goodix_ts_data *ts)
{
	u8 config[GOODIX_CONFIG_MAX_LENGTH];
	int x_max, y_max;
	int error;

	error = goodix_i2c_read(ts->client, ts->chip->config_addr,
				config, ts->chip->config_len);
	if (error) {
		dev_warn(&ts->client->dev, "Error reading config: %d\n",
			 error);
		ts->int_trigger_type = GOODIX_INT_TRIGGER;
		ts->max_touch_num = GOODIX_MAX_CONTACTS;
		return;
	}

	ts->int_trigger_type = config[TRIGGER_LOC] & 0x03;
	ts->max_touch_num = config[MAX_CONTACTS_LOC] & 0x0f;

	x_max = get_unaligned_le16(&config[RESOLUTION_LOC]);
	y_max = get_unaligned_le16(&config[RESOLUTION_LOC + 2]);
	if (x_max && y_max) {
		input_abs_set_max(ts->input_dev, ABS_MT_POSITION_X, x_max - 1);
		input_abs_set_max(ts->input_dev, ABS_MT_POSITION_Y, y_max - 1);
	}
}