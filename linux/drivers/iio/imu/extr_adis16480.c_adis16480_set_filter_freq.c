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
struct adis16480 {int /*<<< orphan*/  adis; TYPE_1__* chip_info; } ;
struct TYPE_2__ {unsigned int* filter_freqs; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int BIT (unsigned int) ; 
 unsigned int** ad16480_filter_data ; 
 int /*<<< orphan*/  adis16480_def_filter_freqs ; 
 int adis_read_reg_16 (int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 
 int adis_write_reg_16 (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 struct adis16480* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16480_set_filter_freq(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, unsigned int freq)
{
	struct adis16480 *st = iio_priv(indio_dev);
	unsigned int enable_mask, offset, reg;
	unsigned int diff, best_diff;
	unsigned int i, best_freq;
	uint16_t val;
	int ret;

	reg = ad16480_filter_data[chan->scan_index][0];
	offset = ad16480_filter_data[chan->scan_index][1];
	enable_mask = BIT(offset + 2);

	ret = adis_read_reg_16(&st->adis, reg, &val);
	if (ret < 0)
		return ret;

	if (freq == 0) {
		val &= ~enable_mask;
	} else {
		best_freq = 0;
		best_diff = st->chip_info->filter_freqs[0];
		for (i = 0; i < ARRAY_SIZE(adis16480_def_filter_freqs); i++) {
			if (st->chip_info->filter_freqs[i] >= freq) {
				diff = st->chip_info->filter_freqs[i] - freq;
				if (diff < best_diff) {
					best_diff = diff;
					best_freq = i;
				}
			}
		}

		val &= ~(0x3 << offset);
		val |= best_freq << offset;
		val |= enable_mask;
	}

	return adis_write_reg_16(&st->adis, reg, val);
}