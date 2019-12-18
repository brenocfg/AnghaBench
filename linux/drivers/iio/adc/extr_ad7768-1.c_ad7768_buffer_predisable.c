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
struct ad7768_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7768_REG_ADC_DATA ; 
 int ad7768_spi_reg_read (struct ad7768_state*,int /*<<< orphan*/ ,int) ; 
 struct ad7768_state* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_predisable (struct iio_dev*) ; 

__attribute__((used)) static int ad7768_buffer_predisable(struct iio_dev *indio_dev)
{
	struct ad7768_state *st = iio_priv(indio_dev);
	int ret;

	/*
	 * To exit continuous read mode, perform a single read of the ADC_DATA
	 * reg (0x2C), which allows further configuration of the device.
	 */
	ret = ad7768_spi_reg_read(st, AD7768_REG_ADC_DATA, 3);
	if (ret < 0)
		return ret;

	return iio_triggered_buffer_predisable(indio_dev);
}