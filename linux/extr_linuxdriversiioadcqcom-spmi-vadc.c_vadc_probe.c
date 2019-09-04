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
typedef  int /*<<< orphan*/  u32 ;
struct vadc_priv {int are_ref_measured; int poll_eoc; int /*<<< orphan*/  nchannels; int /*<<< orphan*/  iio_chans; int /*<<< orphan*/  lock; int /*<<< orphan*/  complete; int /*<<< orphan*/  base; struct device* dev; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_2__ {struct device_node* of_node; struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct regmap* dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vadc_priv*) ; 
 struct vadc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int vadc_check_revision (struct vadc_priv*) ; 
 int vadc_get_dt_data (struct vadc_priv*,struct device_node*) ; 
 int /*<<< orphan*/  vadc_info ; 
 int /*<<< orphan*/  vadc_isr ; 
 int vadc_measure_ref_points (struct vadc_priv*) ; 
 int vadc_reset (struct vadc_priv*) ; 

__attribute__((used)) static int vadc_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct iio_dev *indio_dev;
	struct vadc_priv *vadc;
	struct regmap *regmap;
	int ret, irq_eoc;
	u32 reg;

	regmap = dev_get_regmap(dev->parent, NULL);
	if (!regmap)
		return -ENODEV;

	ret = of_property_read_u32(node, "reg", &reg);
	if (ret < 0)
		return ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*vadc));
	if (!indio_dev)
		return -ENOMEM;

	vadc = iio_priv(indio_dev);
	vadc->regmap = regmap;
	vadc->dev = dev;
	vadc->base = reg;
	vadc->are_ref_measured = false;
	init_completion(&vadc->complete);
	mutex_init(&vadc->lock);

	ret = vadc_check_revision(vadc);
	if (ret)
		return ret;

	ret = vadc_get_dt_data(vadc, node);
	if (ret)
		return ret;

	irq_eoc = platform_get_irq(pdev, 0);
	if (irq_eoc < 0) {
		if (irq_eoc == -EPROBE_DEFER || irq_eoc == -EINVAL)
			return irq_eoc;
		vadc->poll_eoc = true;
	} else {
		ret = devm_request_irq(dev, irq_eoc, vadc_isr, 0,
				       "spmi-vadc", vadc);
		if (ret)
			return ret;
	}

	ret = vadc_reset(vadc);
	if (ret) {
		dev_err(dev, "reset failed\n");
		return ret;
	}

	ret = vadc_measure_ref_points(vadc);
	if (ret)
		return ret;

	indio_dev->dev.parent = dev;
	indio_dev->dev.of_node = node;
	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &vadc_info;
	indio_dev->channels = vadc->iio_chans;
	indio_dev->num_channels = vadc->nchannels;

	return devm_iio_device_register(dev, indio_dev);
}