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
struct ad7877 {unsigned int* conversion_data; unsigned int x_plate_ohms; unsigned int pressure_max; int /*<<< orphan*/  timer; struct input_dev* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 size_t AD7877_SEQ_XPOS ; 
 size_t AD7877_SEQ_YPOS ; 
 size_t AD7877_SEQ_Z1 ; 
 size_t AD7877_SEQ_Z2 ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int EINVAL ; 
 unsigned int MAX_12BIT ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7877_process_data(struct ad7877 *ts)
{
	struct input_dev *input_dev = ts->input;
	unsigned Rt;
	u16 x, y, z1, z2;

	x = ts->conversion_data[AD7877_SEQ_XPOS] & MAX_12BIT;
	y = ts->conversion_data[AD7877_SEQ_YPOS] & MAX_12BIT;
	z1 = ts->conversion_data[AD7877_SEQ_Z1] & MAX_12BIT;
	z2 = ts->conversion_data[AD7877_SEQ_Z2] & MAX_12BIT;

	/*
	 * The samples processed here are already preprocessed by the AD7877.
	 * The preprocessing function consists of an averaging filter.
	 * The combination of 'first conversion delay' and averaging provides a robust solution,
	 * discarding the spurious noise in the signal and keeping only the data of interest.
	 * The size of the averaging filter is programmable. (dev.platform_data, see linux/spi/ad7877.h)
	 * Other user-programmable conversion controls include variable acquisition time,
	 * and first conversion delay. Up to 16 averages can be taken per conversion.
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
		if (Rt > ts->pressure_max)
			return -EINVAL;

		if (!timer_pending(&ts->timer))
			input_report_key(input_dev, BTN_TOUCH, 1);

		input_report_abs(input_dev, ABS_X, x);
		input_report_abs(input_dev, ABS_Y, y);
		input_report_abs(input_dev, ABS_PRESSURE, Rt);
		input_sync(input_dev);

		return 0;
	}

	return -EINVAL;
}