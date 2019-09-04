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
typedef  unsigned int const u8 ;
struct bu21013_ts_data {int /*<<< orphan*/  in_dev; TYPE_1__* chip; } ;
struct TYPE_2__ {unsigned int touch_x_max; unsigned int touch_y_max; scalar_t__ y_flip; scalar_t__ x_flip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 unsigned int const BU21013_SENSORS_EN_0_7 ; 
 unsigned int const BU21013_SENSORS_EN_16_23 ; 
 unsigned int const BU21013_SENSORS_EN_8_15 ; 
 scalar_t__ DELTA_MIN ; 
 int EINVAL ; 
 int LENGTH_OF_BUFFER ; 
 unsigned int const MASK_BITS ; 
 int MAX_FINGERS ; 
 unsigned int const SHIFT_2 ; 
 unsigned int const SHIFT_8 ; 
 scalar_t__ abs (unsigned int) ; 
 scalar_t__ bu21013_read_block_data (struct bu21013_ts_data*,unsigned int const*) ; 
 int hweight32 (unsigned int const) ; 
 int /*<<< orphan*/  input_mt_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bu21013_do_touch_report(struct bu21013_ts_data *data)
{
	u8	buf[LENGTH_OF_BUFFER];
	unsigned int pos_x[2], pos_y[2];
	bool	has_x_sensors, has_y_sensors;
	int	finger_down_count = 0;
	int	i;

	if (data == NULL)
		return -EINVAL;

	if (bu21013_read_block_data(data, buf) < 0)
		return -EINVAL;

	has_x_sensors = hweight32(buf[0] & BU21013_SENSORS_EN_0_7);
	has_y_sensors = hweight32(((buf[1] & BU21013_SENSORS_EN_8_15) |
		((buf[2] & BU21013_SENSORS_EN_16_23) << SHIFT_8)) >> SHIFT_2);
	if (!has_x_sensors || !has_y_sensors)
		return 0;

	for (i = 0; i < MAX_FINGERS; i++) {
		const u8 *p = &buf[4 * i + 3];
		unsigned int x = p[0] << SHIFT_2 | (p[1] & MASK_BITS);
		unsigned int y = p[2] << SHIFT_2 | (p[3] & MASK_BITS);
		if (x == 0 || y == 0)
			continue;
		pos_x[finger_down_count] = x;
		pos_y[finger_down_count] = y;
		finger_down_count++;
	}

	if (finger_down_count) {
		if (finger_down_count == 2 &&
		    (abs(pos_x[0] - pos_x[1]) < DELTA_MIN ||
		     abs(pos_y[0] - pos_y[1]) < DELTA_MIN)) {
			return 0;
		}

		for (i = 0; i < finger_down_count; i++) {
			if (data->chip->x_flip)
				pos_x[i] = data->chip->touch_x_max - pos_x[i];
			if (data->chip->y_flip)
				pos_y[i] = data->chip->touch_y_max - pos_y[i];

			input_report_abs(data->in_dev,
					 ABS_MT_POSITION_X, pos_x[i]);
			input_report_abs(data->in_dev,
					 ABS_MT_POSITION_Y, pos_y[i]);
			input_mt_sync(data->in_dev);
		}
	} else
		input_mt_sync(data->in_dev);

	input_sync(data->in_dev);

	return 0;
}