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
struct iio_chan_spec {int dummy; } ;
struct ad5380_state {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int AD5380_CTRL_PWR_DOWN_MODE_OFFSET ; 
 int /*<<< orphan*/  AD5380_REG_SF_CTRL ; 
 struct ad5380_state* iio_priv (struct iio_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int ad5380_set_powerdown_mode(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, unsigned int mode)
{
	struct ad5380_state *st = iio_priv(indio_dev);
	int ret;

	ret = regmap_update_bits(st->regmap, AD5380_REG_SF_CTRL,
		1 << AD5380_CTRL_PWR_DOWN_MODE_OFFSET,
		mode << AD5380_CTRL_PWR_DOWN_MODE_OFFSET);

	return ret;
}