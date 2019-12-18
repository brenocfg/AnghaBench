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
struct device {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_2__ {struct device_node* of_node; struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct iadc_chip {int poll_eoc; struct device* dev; int /*<<< orphan*/ * rsense; int /*<<< orphan*/  base; int /*<<< orphan*/  lock; int /*<<< orphan*/  complete; int /*<<< orphan*/  regmap; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 size_t IADC_EXT_RSENSE ; 
 size_t IADC_INT_RSENSE ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct iadc_chip*) ; 
 int /*<<< orphan*/  enable_irq_wake (int) ; 
 int /*<<< orphan*/  iadc_channels ; 
 int /*<<< orphan*/  iadc_info ; 
 int /*<<< orphan*/  iadc_isr ; 
 int iadc_reset (struct iadc_chip*) ; 
 int iadc_rsense_read (struct iadc_chip*,struct device_node*) ; 
 int iadc_update_offset (struct iadc_chip*) ; 
 int iadc_version_check (struct iadc_chip*) ; 
 struct iadc_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iadc_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct iio_dev *indio_dev;
	struct iadc_chip *iadc;
	int ret, irq_eoc;
	u32 res;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*iadc));
	if (!indio_dev)
		return -ENOMEM;

	iadc = iio_priv(indio_dev);
	iadc->dev = dev;

	iadc->regmap = dev_get_regmap(dev->parent, NULL);
	if (!iadc->regmap)
		return -ENODEV;

	init_completion(&iadc->complete);
	mutex_init(&iadc->lock);

	ret = of_property_read_u32(node, "reg", &res);
	if (ret < 0)
		return -ENODEV;

	iadc->base = res;

	ret = iadc_version_check(iadc);
	if (ret < 0)
		return -ENODEV;

	ret = iadc_rsense_read(iadc, node);
	if (ret < 0)
		return -ENODEV;

	dev_dbg(iadc->dev, "sense resistors %d and %d micro Ohm\n",
		iadc->rsense[IADC_INT_RSENSE],
		iadc->rsense[IADC_EXT_RSENSE]);

	irq_eoc = platform_get_irq(pdev, 0);
	if (irq_eoc == -EPROBE_DEFER)
		return irq_eoc;

	if (irq_eoc < 0)
		iadc->poll_eoc = true;

	ret = iadc_reset(iadc);
	if (ret < 0) {
		dev_err(dev, "reset failed\n");
		return ret;
	}

	if (!iadc->poll_eoc) {
		ret = devm_request_irq(dev, irq_eoc, iadc_isr, 0,
					"spmi-iadc", iadc);
		if (!ret)
			enable_irq_wake(irq_eoc);
		else
			return ret;
	} else {
		device_init_wakeup(iadc->dev, 1);
	}

	ret = iadc_update_offset(iadc);
	if (ret < 0) {
		dev_err(dev, "failed offset calibration\n");
		return ret;
	}

	indio_dev->dev.parent = dev;
	indio_dev->dev.of_node = node;
	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &iadc_info;
	indio_dev->channels = iadc_channels;
	indio_dev->num_channels = ARRAY_SIZE(iadc_channels);

	return devm_iio_device_register(dev, indio_dev);
}