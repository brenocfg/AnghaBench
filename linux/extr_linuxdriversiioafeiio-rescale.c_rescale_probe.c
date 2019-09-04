#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rescale {int numerator; int denominator; struct iio_chan_spec_ext_info* ext_info; int /*<<< orphan*/  chan; struct iio_channel* source; TYPE_3__* cfg; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {struct device* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/ * channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct iio_channel {TYPE_2__* channel; } ;
struct iio_chan_spec_ext_info {int private; int /*<<< orphan*/  write; int /*<<< orphan*/  read; scalar_t__ name; } ;
struct TYPE_8__ {scalar_t__ write; scalar_t__ read; } ;
struct TYPE_7__ {int (* props ) (struct device*,struct rescale*) ;} ;
struct TYPE_6__ {TYPE_4__* ext_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (struct iio_channel*) ; 
 int PTR_ERR (struct iio_channel*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct iio_channel* devm_iio_channel_get (struct device*,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 struct iio_chan_spec_ext_info* devm_kmemdup (struct device*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int iio_get_channel_ext_info_count (struct iio_channel*) ; 
 struct rescale* iio_priv (struct iio_dev*) ; 
 TYPE_3__* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int rescale_configure_channel (struct device*,struct rescale*) ; 
 int /*<<< orphan*/  rescale_info ; 
 int /*<<< orphan*/  rescale_read_ext_info ; 
 int /*<<< orphan*/  rescale_write_ext_info ; 
 int stub1 (struct device*,struct rescale*) ; 

__attribute__((used)) static int rescale_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct iio_dev *indio_dev;
	struct iio_channel *source;
	struct rescale *rescale;
	int sizeof_ext_info;
	int sizeof_priv;
	int i;
	int ret;

	source = devm_iio_channel_get(dev, NULL);
	if (IS_ERR(source)) {
		if (PTR_ERR(source) != -EPROBE_DEFER)
			dev_err(dev, "failed to get source channel\n");
		return PTR_ERR(source);
	}

	sizeof_ext_info = iio_get_channel_ext_info_count(source);
	if (sizeof_ext_info) {
		sizeof_ext_info += 1; /* one extra entry for the sentinel */
		sizeof_ext_info *= sizeof(*rescale->ext_info);
	}

	sizeof_priv = sizeof(*rescale) + sizeof_ext_info;

	indio_dev = devm_iio_device_alloc(dev, sizeof_priv);
	if (!indio_dev)
		return -ENOMEM;

	rescale = iio_priv(indio_dev);

	rescale->cfg = of_device_get_match_data(dev);
	rescale->numerator = 1;
	rescale->denominator = 1;

	ret = rescale->cfg->props(dev, rescale);
	if (ret)
		return ret;

	if (!rescale->numerator || !rescale->denominator) {
		dev_err(dev, "invalid scaling factor.\n");
		return -EINVAL;
	}

	platform_set_drvdata(pdev, indio_dev);

	rescale->source = source;

	indio_dev->name = dev_name(dev);
	indio_dev->dev.parent = dev;
	indio_dev->info = &rescale_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = &rescale->chan;
	indio_dev->num_channels = 1;
	if (sizeof_ext_info) {
		rescale->ext_info = devm_kmemdup(dev,
						 source->channel->ext_info,
						 sizeof_ext_info, GFP_KERNEL);
		if (!rescale->ext_info)
			return -ENOMEM;

		for (i = 0; rescale->ext_info[i].name; ++i) {
			struct iio_chan_spec_ext_info *ext_info =
				&rescale->ext_info[i];

			if (source->channel->ext_info[i].read)
				ext_info->read = rescale_read_ext_info;
			if (source->channel->ext_info[i].write)
				ext_info->write = rescale_write_ext_info;
			ext_info->private = i;
		}
	}

	ret = rescale_configure_channel(dev, rescale);
	if (ret)
		return ret;

	return devm_iio_device_register(dev, indio_dev);
}