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
typedef  unsigned int uint16_t ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t scan_index; } ;
struct adis16480 {TYPE_1__* chip_info; int /*<<< orphan*/  adis; } ;
struct TYPE_2__ {int* filter_freqs; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int IIO_VAL_INT ; 
 unsigned int** ad16480_filter_data ; 
 int adis_read_reg_16 (int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 
 struct adis16480* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16480_get_filter_freq(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, int *freq)
{
	struct adis16480 *st = iio_priv(indio_dev);
	unsigned int enable_mask, offset, reg;
	uint16_t val;
	int ret;

	reg = ad16480_filter_data[chan->scan_index][0];
	offset = ad16480_filter_data[chan->scan_index][1];
	enable_mask = BIT(offset + 2);

	ret = adis_read_reg_16(&st->adis, reg, &val);
	if (ret < 0)
		return ret;

	if (!(val & enable_mask))
		*freq = 0;
	else
		*freq = st->chip_info->filter_freqs[(val >> offset) & 0x3];

	return IIO_VAL_INT;
}