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
struct ad7949_adc_chip {unsigned int cfg; } ;

/* Variables and functions */
 unsigned int AD7949_MASK_TOTAL ; 
 int ad7949_spi_write_cfg (struct ad7949_adc_chip*,unsigned int,unsigned int) ; 
 struct ad7949_adc_chip* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7949_spi_reg_access(struct iio_dev *indio_dev,
			unsigned int reg, unsigned int writeval,
			unsigned int *readval)
{
	struct ad7949_adc_chip *ad7949_adc = iio_priv(indio_dev);
	int ret = 0;

	if (readval)
		*readval = ad7949_adc->cfg;
	else
		ret = ad7949_spi_write_cfg(ad7949_adc,
			writeval & AD7949_MASK_TOTAL, AD7949_MASK_TOTAL);

	return ret;
}