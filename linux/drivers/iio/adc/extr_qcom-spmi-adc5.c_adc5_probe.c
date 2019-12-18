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
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_2__ {struct device_node* of_node; struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct adc5_chip {int poll_eoc; int /*<<< orphan*/  nchannels; int /*<<< orphan*/  iio_chans; int /*<<< orphan*/  lock; int /*<<< orphan*/  complete; int /*<<< orphan*/  base; struct device* dev; struct regmap* regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int adc5_get_dt_data (struct adc5_chip*,struct device_node*) ; 
 int /*<<< orphan*/  adc5_info ; 
 int /*<<< orphan*/  adc5_isr ; 
 struct regmap* dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct adc5_chip*) ; 
 struct adc5_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int adc5_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct iio_dev *indio_dev;
	struct adc5_chip *adc;
	struct regmap *regmap;
	int ret, irq_eoc;
	u32 reg;

	regmap = dev_get_regmap(dev->parent, NULL);
	if (!regmap)
		return -ENODEV;

	ret = of_property_read_u32(node, "reg", &reg);
	if (ret < 0)
		return ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*adc));
	if (!indio_dev)
		return -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->regmap = regmap;
	adc->dev = dev;
	adc->base = reg;
	init_completion(&adc->complete);
	mutex_init(&adc->lock);

	ret = adc5_get_dt_data(adc, node);
	if (ret) {
		pr_err("adc get dt data failed\n");
		return ret;
	}

	irq_eoc = platform_get_irq(pdev, 0);
	if (irq_eoc < 0) {
		if (irq_eoc == -EPROBE_DEFER || irq_eoc == -EINVAL)
			return irq_eoc;
		adc->poll_eoc = true;
	} else {
		ret = devm_request_irq(dev, irq_eoc, adc5_isr, 0,
				       "pm-adc5", adc);
		if (ret)
			return ret;
	}

	indio_dev->dev.parent = dev;
	indio_dev->dev.of_node = node;
	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &adc5_info;
	indio_dev->channels = adc->iio_chans;
	indio_dev->num_channels = adc->nchannels;

	return devm_iio_device_register(dev, indio_dev);
}