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
 int /*<<< orphan*/  AD7768_REG_INTERFACE_FORMAT ; 
 int ad7768_spi_reg_write (struct ad7768_state*,int /*<<< orphan*/ ,int) ; 
 struct ad7768_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_postenable (struct iio_dev*) ; 

__attribute__((used)) static int ad7768_buffer_postenable(struct iio_dev *indio_dev)
{
	struct ad7768_state *st = iio_priv(indio_dev);

	iio_triggered_buffer_postenable(indio_dev);
	/*
	 * Write a 1 to the LSB of the INTERFACE_FORMAT register to enter
	 * continuous read mode. Subsequent data reads do not require an
	 * initial 8-bit write to query the ADC_DATA register.
	 */
	return ad7768_spi_reg_write(st, AD7768_REG_INTERFACE_FORMAT, 0x01);
}