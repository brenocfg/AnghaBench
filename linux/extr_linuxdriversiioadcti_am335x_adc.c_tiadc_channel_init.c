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
struct tiadc_device {size_t* channel_line; } ;
struct iio_dev {int num_channels; struct iio_chan_spec* channels; } ;
struct TYPE_2__ {unsigned char sign; int realbits; int storagebits; } ;
struct iio_chan_spec {int indexed; size_t channel; int scan_index; TYPE_1__ scan_type; int /*<<< orphan*/  datasheet_name; int /*<<< orphan*/  info_mask_separate; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_RAW ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int /*<<< orphan*/ * chan_name_ain ; 
 struct tiadc_device* iio_priv (struct iio_dev*) ; 
 struct iio_chan_spec* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tiadc_channel_init(struct iio_dev *indio_dev, int channels)
{
	struct tiadc_device *adc_dev = iio_priv(indio_dev);
	struct iio_chan_spec *chan_array;
	struct iio_chan_spec *chan;
	int i;

	indio_dev->num_channels = channels;
	chan_array = kcalloc(channels, sizeof(*chan_array), GFP_KERNEL);
	if (chan_array == NULL)
		return -ENOMEM;

	chan = chan_array;
	for (i = 0; i < channels; i++, chan++) {

		chan->type = IIO_VOLTAGE;
		chan->indexed = 1;
		chan->channel = adc_dev->channel_line[i];
		chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
		chan->datasheet_name = chan_name_ain[chan->channel];
		chan->scan_index = i;
		chan->scan_type.sign = 'u';
		chan->scan_type.realbits = 12;
		chan->scan_type.storagebits = 16;
	}

	indio_dev->channels = chan_array;

	return 0;
}