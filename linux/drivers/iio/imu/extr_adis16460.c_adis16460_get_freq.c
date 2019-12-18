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
typedef  int uint16_t ;
struct iio_dev {int dummy; } ;
struct adis16460 {int /*<<< orphan*/  adis; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16460_REG_DEC_RATE ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int adis_read_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 struct adis16460* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16460_get_freq(struct iio_dev *indio_dev, int *val, int *val2)
{
	struct adis16460 *st = iio_priv(indio_dev);
	uint16_t t;
	int ret;
	unsigned int freq;

	ret = adis_read_reg_16(&st->adis, ADIS16460_REG_DEC_RATE, &t);
	if (ret < 0)
		return ret;

	freq = 2048000 / (t + 1);
	*val = freq / 1000;
	*val2 = (freq % 1000) * 1000;

	return IIO_VAL_INT_PLUS_MICRO;
}