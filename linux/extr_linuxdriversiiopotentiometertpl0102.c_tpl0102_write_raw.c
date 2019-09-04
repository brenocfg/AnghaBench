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
struct tpl0102_data {size_t devid; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int max_pos; } ;

/* Variables and functions */
 int EINVAL ; 
 long IIO_CHAN_INFO_RAW ; 
 struct tpl0102_data* iio_priv (struct iio_dev*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* tpl0102_cfg ; 

__attribute__((used)) static int tpl0102_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct tpl0102_data *data = iio_priv(indio_dev);

	if (mask != IIO_CHAN_INFO_RAW)
		return -EINVAL;

	if (val >= tpl0102_cfg[data->devid].max_pos || val < 0)
		return -EINVAL;

	return regmap_write(data->regmap, chan->channel, val);
}