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
 unsigned int AD5380_CTRL_PWR_DOWN_MODE_OFFSET ; 
 int /*<<< orphan*/  AD5380_REG_SF_CTRL ; 
 struct ad5380_state* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ad5380_get_powerdown_mode(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan)
{
	struct ad5380_state *st = iio_priv(indio_dev);
	unsigned int mode;
	int ret;

	ret = regmap_read(st->regmap, AD5380_REG_SF_CTRL, &mode);
	if (ret)
		return ret;

	mode = (mode >> AD5380_CTRL_PWR_DOWN_MODE_OFFSET) & 1;

	return mode;
}