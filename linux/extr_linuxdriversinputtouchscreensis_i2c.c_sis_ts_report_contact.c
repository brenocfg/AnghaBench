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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct sis_ts_data {TYPE_1__* client; struct input_dev* input; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 scalar_t__ SIS_ALL_IN_ONE_PACKAGE ; 
 scalar_t__ SIS_AREA_UNIT ; 
 size_t SIS_CONTACT_HEIGHT_OFFSET ; 
 size_t SIS_CONTACT_ID_OFFSET ; 
 size_t SIS_CONTACT_PRESSURE_OFFSET (scalar_t__) ; 
 size_t SIS_CONTACT_STATUS_OFFSET ; 
 size_t SIS_CONTACT_WIDTH_OFFSET ; 
 size_t SIS_CONTACT_X_OFFSET ; 
 size_t SIS_CONTACT_Y_OFFSET ; 
 scalar_t__ SIS_PKT_HAS_AREA (scalar_t__) ; 
 scalar_t__ SIS_PKT_HAS_PRESSURE (scalar_t__) ; 
 scalar_t__ SIS_STATUS_DOWN ; 
 scalar_t__ SIS_STATUS_UP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__ const) ; 
 scalar_t__ get_unaligned_le16 (scalar_t__ const*) ; 
 int input_mt_get_slot_by_key (struct input_dev*,scalar_t__ const) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sis_ts_report_contact(struct sis_ts_data *ts, const u8 *data, u8 id)
{
	struct input_dev *input = ts->input;
	int slot;
	u8 status = data[SIS_CONTACT_STATUS_OFFSET];
	u8 pressure;
	u8 height, width;
	u16 x, y;

	if (status != SIS_STATUS_DOWN && status != SIS_STATUS_UP) {
		dev_err(&ts->client->dev, "Unexpected touch status: %#02x\n",
			data[SIS_CONTACT_STATUS_OFFSET]);
		return -EINVAL;
	}

	slot = input_mt_get_slot_by_key(input, data[SIS_CONTACT_ID_OFFSET]);
	if (slot < 0)
		return -ENOENT;

	input_mt_slot(input, slot);
	input_mt_report_slot_state(input, MT_TOOL_FINGER,
				   status == SIS_STATUS_DOWN);

	if (status == SIS_STATUS_DOWN) {
		pressure = height = width = 1;
		if (id != SIS_ALL_IN_ONE_PACKAGE) {
			if (SIS_PKT_HAS_AREA(id)) {
				width = data[SIS_CONTACT_WIDTH_OFFSET];
				height = data[SIS_CONTACT_HEIGHT_OFFSET];
			}

			if (SIS_PKT_HAS_PRESSURE(id))
				pressure =
					data[SIS_CONTACT_PRESSURE_OFFSET(id)];
		}

		x = get_unaligned_le16(&data[SIS_CONTACT_X_OFFSET]);
		y = get_unaligned_le16(&data[SIS_CONTACT_Y_OFFSET]);

		input_report_abs(input, ABS_MT_TOUCH_MAJOR,
				 width * SIS_AREA_UNIT);
		input_report_abs(input, ABS_MT_TOUCH_MINOR,
				 height * SIS_AREA_UNIT);
		input_report_abs(input, ABS_MT_PRESSURE, pressure);
		input_report_abs(input, ABS_MT_POSITION_X, x);
		input_report_abs(input, ABS_MT_POSITION_Y, y);
	}

	return 0;
}