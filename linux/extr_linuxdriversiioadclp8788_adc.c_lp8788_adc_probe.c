#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct lp8788_adc {int /*<<< orphan*/  lock; struct lp8788* lp; } ;
struct lp8788 {int /*<<< orphan*/  pdata; } ;
struct TYPE_4__ {TYPE_2__* parent; int /*<<< orphan*/  of_node; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct lp8788* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_map_array_unregister (struct iio_dev*) ; 
 struct lp8788_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  lp8788_adc_channels ; 
 int /*<<< orphan*/  lp8788_adc_info ; 
 int lp8788_iio_map_register (struct iio_dev*,int /*<<< orphan*/ ,struct lp8788_adc*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 

__attribute__((used)) static int lp8788_adc_probe(struct platform_device *pdev)
{
	struct lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	struct iio_dev *indio_dev;
	struct lp8788_adc *adc;
	int ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*adc));
	if (!indio_dev)
		return -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->lp = lp;
	platform_set_drvdata(pdev, indio_dev);

	indio_dev->dev.of_node = pdev->dev.of_node;
	ret = lp8788_iio_map_register(indio_dev, lp->pdata, adc);
	if (ret)
		return ret;

	mutex_init(&adc->lock);

	indio_dev->dev.parent = &pdev->dev;
	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &lp8788_adc_info;
	indio_dev->channels = lp8788_adc_channels;
	indio_dev->num_channels = ARRAY_SIZE(lp8788_adc_channels);

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&pdev->dev, "iio dev register err: %d\n", ret);
		goto err_iio_device;
	}

	return 0;

err_iio_device:
	iio_map_array_unregister(indio_dev);
	return ret;
}