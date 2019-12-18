#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {unsigned int* active_scan_mask; int /*<<< orphan*/  masklength; } ;
struct adxl372_state {int fifo_set_size; int watermark; int /*<<< orphan*/  fifo_mode; int /*<<< orphan*/  fifo_format; } ;
struct TYPE_3__ {unsigned int bits; int /*<<< orphan*/  fifo_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADXL372_FIFO_BYPASSED ; 
 int ADXL372_FIFO_SIZE ; 
 int /*<<< orphan*/  ADXL372_FIFO_STREAMED ; 
 int /*<<< orphan*/  ADXL372_INT1_MAP_FIFO_FULL_MSK ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* adxl372_axis_lookup_table ; 
 int adxl372_configure_fifo (struct adxl372_state*) ; 
 int adxl372_set_interrupts (struct adxl372_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bitmap_weight (unsigned int*,int /*<<< orphan*/ ) ; 
 struct adxl372_state* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_postenable (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_predisable (struct iio_dev*) ; 

__attribute__((used)) static int adxl372_buffer_postenable(struct iio_dev *indio_dev)
{
	struct adxl372_state *st = iio_priv(indio_dev);
	unsigned int mask;
	int i, ret;

	ret = iio_triggered_buffer_postenable(indio_dev);
	if (ret < 0)
		return ret;

	ret = adxl372_set_interrupts(st, ADXL372_INT1_MAP_FIFO_FULL_MSK, 0);
	if (ret < 0)
		goto err;

	mask = *indio_dev->active_scan_mask;

	for (i = 0; i < ARRAY_SIZE(adxl372_axis_lookup_table); i++) {
		if (mask == adxl372_axis_lookup_table[i].bits)
			break;
	}

	if (i == ARRAY_SIZE(adxl372_axis_lookup_table)) {
		ret = -EINVAL;
		goto err;
	}

	st->fifo_format = adxl372_axis_lookup_table[i].fifo_format;
	st->fifo_set_size = bitmap_weight(indio_dev->active_scan_mask,
					  indio_dev->masklength);
	/*
	 * The 512 FIFO samples can be allotted in several ways, such as:
	 * 170 sample sets of concurrent 3-axis data
	 * 256 sample sets of concurrent 2-axis data (user selectable)
	 * 512 sample sets of single-axis data
	 */
	if ((st->watermark * st->fifo_set_size) > ADXL372_FIFO_SIZE)
		st->watermark = (ADXL372_FIFO_SIZE  / st->fifo_set_size);

	st->fifo_mode = ADXL372_FIFO_STREAMED;

	ret = adxl372_configure_fifo(st);
	if (ret < 0) {
		st->fifo_mode = ADXL372_FIFO_BYPASSED;
		adxl372_set_interrupts(st, 0, 0);
		goto err;
	}

	return 0;

err:
	iio_triggered_buffer_predisable(indio_dev);
	return ret;
}