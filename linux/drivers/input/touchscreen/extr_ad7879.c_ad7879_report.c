#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int u16 ;
struct input_dev {int dummy; } ;
struct ad7879 {unsigned int* conversion_data; unsigned int x_plate_ohms; unsigned int x; unsigned int y; unsigned int Rt; int /*<<< orphan*/  timer; scalar_t__ swap_xy; struct input_dev* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 size_t AD7879_SEQ_XPOS ; 
 size_t AD7879_SEQ_YPOS ; 
 size_t AD7879_SEQ_Z1 ; 
 size_t AD7879_SEQ_Z2 ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int EINVAL ; 
 unsigned int MAX_12BIT ; 
 unsigned int input_abs_get_max (struct input_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  swap (unsigned int,unsigned int) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7879_report(struct ad7879 *ts)
{
	struct input_dev *input_dev = ts->input;
	unsigned Rt;
	u16 x, y, z1, z2;

	x = ts->conversion_data[AD7879_SEQ_XPOS] & MAX_12BIT;
	y = ts->conversion_data[AD7879_SEQ_YPOS] & MAX_12BIT;
	z1 = ts->conversion_data[AD7879_SEQ_Z1] & MAX_12BIT;
	z2 = ts->conversion_data[AD7879_SEQ_Z2] & MAX_12BIT;

	if (ts->swap_xy)
		swap(x, y);

	/*
	 * The samples processed here are already preprocessed by the AD7879.
	 * The preprocessing function consists of a median and an averaging
	 * filter.  The combination of these two techniques provides a robust
	 * solution, discarding the spurious noise in the signal and keeping
	 * only the data of interest.  The size of both filters is
	 * programmable. (dev.platform_data, see linux/platform_data/ad7879.h)
	 * Other user-programmable conversion controls include variable
	 * acquisition time, and first conversion delay. Up to 16 averages can
	 * be taken per conversion.
	 */

	if (likely(x && z1)) {
		/* compute touch pressure resistance using equation #1 */
		Rt = (z2 - z1) * x * ts->x_plate_ohms;
		Rt /= z1;
		Rt = (Rt + 2047) >> 12;

		/*
		 * Sample found inconsistent, pressure is beyond
		 * the maximum. Don't report it to user space.
		 */
		if (Rt > input_abs_get_max(input_dev, ABS_PRESSURE))
			return -EINVAL;

		/*
		 * Note that we delay reporting events by one sample.
		 * This is done to avoid reporting last sample of the
		 * touch sequence, which may be incomplete if finger
		 * leaves the surface before last reading is taken.
		 */
		if (timer_pending(&ts->timer)) {
			/* Touch continues */
			input_report_key(input_dev, BTN_TOUCH, 1);
			input_report_abs(input_dev, ABS_X, ts->x);
			input_report_abs(input_dev, ABS_Y, ts->y);
			input_report_abs(input_dev, ABS_PRESSURE, ts->Rt);
			input_sync(input_dev);
		}

		ts->x = x;
		ts->y = y;
		ts->Rt = Rt;

		return 0;
	}

	return -EINVAL;
}