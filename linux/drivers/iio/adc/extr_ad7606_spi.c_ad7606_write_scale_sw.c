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
 int /*<<< orphan*/  AD7606_RANGE_CH_ADDR (int) ; 
 int /*<<< orphan*/  AD7606_RANGE_CH_MODE (int,int) ; 
 int /*<<< orphan*/  AD7606_RANGE_CH_MSK (int) ; 
 int ad7606_spi_write_mask (struct ad7606_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7606_write_scale_sw(struct iio_dev *indio_dev, int ch, int val)
{
	struct ad7606_state *st = iio_priv(indio_dev);

	return ad7606_spi_write_mask(st,
				     AD7606_RANGE_CH_ADDR(ch),
				     AD7606_RANGE_CH_MSK(ch),
				     AD7606_RANGE_CH_MODE(ch, val));
}