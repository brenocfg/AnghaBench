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
struct ad7606_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7606_OS_MODE ; 
 int ad7606_spi_reg_write (struct ad7606_state*,int /*<<< orphan*/ ,int) ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7606_write_os_sw(struct iio_dev *indio_dev, int val)
{
	struct ad7606_state *st = iio_priv(indio_dev);

	return ad7606_spi_reg_write(st, AD7606_OS_MODE, val);
}