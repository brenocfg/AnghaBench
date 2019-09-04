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
struct iio_chan_spec {int indexed; int info_mask_separate; int info_mask_separate_available; int /*<<< orphan*/  type; int /*<<< orphan*/  ext_info; int /*<<< orphan*/  output; } ;
struct rescale {TYPE_2__* cfg; int /*<<< orphan*/  ext_info; TYPE_1__* source; struct iio_chan_spec chan; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {struct iio_chan_spec* channel; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_RAW ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_SCALE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ iio_channel_has_available (struct iio_chan_spec const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_channel_has_info (struct iio_chan_spec const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rescale_configure_channel(struct device *dev,
				     struct rescale *rescale)
{
	struct iio_chan_spec *chan = &rescale->chan;
	struct iio_chan_spec const *schan = rescale->source->channel;

	chan->indexed = 1;
	chan->output = schan->output;
	chan->ext_info = rescale->ext_info;
	chan->type = rescale->cfg->type;

	if (!iio_channel_has_info(schan, IIO_CHAN_INFO_RAW) ||
	    !iio_channel_has_info(schan, IIO_CHAN_INFO_SCALE)) {
		dev_err(dev, "source channel does not support raw/scale\n");
		return -EINVAL;
	}

	chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_SCALE);

	if (iio_channel_has_available(schan, IIO_CHAN_INFO_RAW))
		chan->info_mask_separate_available |= BIT(IIO_CHAN_INFO_RAW);

	return 0;
}