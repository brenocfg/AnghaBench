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
struct iio_dev {int dummy; } ;
struct adis16136 {int /*<<< orphan*/  adis; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16136_REG_AVG_CNT ; 
 int ARRAY_SIZE (unsigned int*) ; 
 unsigned int* adis16136_3db_divisors ; 
 int adis16136_get_freq (struct adis16136*,unsigned int*) ; 
 int adis_write_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct adis16136* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16136_set_filter(struct iio_dev *indio_dev, int val)
{
	struct adis16136 *adis16136 = iio_priv(indio_dev);
	unsigned int freq;
	int i, ret;

	ret = adis16136_get_freq(adis16136, &freq);
	if (ret < 0)
		return ret;

	for (i = ARRAY_SIZE(adis16136_3db_divisors) - 1; i >= 1; i--) {
		if (freq / adis16136_3db_divisors[i] >= val)
			break;
	}

	return adis_write_reg_16(&adis16136->adis, ADIS16136_REG_AVG_CNT, i);
}