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
struct ltc1660_priv {int* value; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int shift; int /*<<< orphan*/  realbits; } ;
struct iio_chan_spec {size_t channel; TYPE_1__ scan_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IIO_CHAN_INFO_RAW 128 
 struct ltc1660_priv* iio_priv (struct iio_dev*) ; 
 int regmap_write (int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static int ltc1660_write_raw(struct iio_dev *indio_dev,
		struct iio_chan_spec const *chan,
		int val,
		int val2,
		long mask)
{
	struct ltc1660_priv *priv = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (val2 != 0)
			return -EINVAL;

		if (val < 0 || val > GENMASK(chan->scan_type.realbits - 1, 0))
			return -EINVAL;

		ret = regmap_write(priv->regmap, chan->channel,
					(val << chan->scan_type.shift));
		if (!ret)
			priv->value[chan->channel] = val;

		return ret;
	default:
		return -EINVAL;
	}
}