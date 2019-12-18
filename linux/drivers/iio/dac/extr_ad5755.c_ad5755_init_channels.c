#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {struct iio_chan_spec* channels; } ;
struct iio_chan_spec {unsigned int channel; unsigned int address; int /*<<< orphan*/  type; } ;
struct ad5755_state {TYPE_1__* chip_info; struct iio_chan_spec* channels; } ;
struct ad5755_platform_data {TYPE_2__* dac; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {struct iio_chan_spec channel_template; } ;

/* Variables and functions */
 unsigned int AD5755_NUM_CHANNELS ; 
 int /*<<< orphan*/  IIO_CURRENT ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 scalar_t__ ad5755_is_voltage_mode (int /*<<< orphan*/ ) ; 
 struct ad5755_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5755_init_channels(struct iio_dev *indio_dev,
				const struct ad5755_platform_data *pdata)
{
	struct ad5755_state *st = iio_priv(indio_dev);
	struct iio_chan_spec *channels = st->channels;
	unsigned int i;

	for (i = 0; i < AD5755_NUM_CHANNELS; ++i) {
		channels[i] = st->chip_info->channel_template;
		channels[i].channel = i;
		channels[i].address = i;
		if (pdata && ad5755_is_voltage_mode(pdata->dac[i].mode))
			channels[i].type = IIO_VOLTAGE;
		else
			channels[i].type = IIO_CURRENT;
	}

	indio_dev->channels = channels;

	return 0;
}