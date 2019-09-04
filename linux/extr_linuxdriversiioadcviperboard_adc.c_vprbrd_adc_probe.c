#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vprbrd_adc {struct vprbrd* vb; } ;
struct vprbrd {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {TYPE_2__* parent; } ;
struct iio_dev {char* name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct vprbrd* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_iio_device_register (TYPE_2__*,struct iio_dev*) ; 
 struct vprbrd_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  vprbrd_adc_iio_channels ; 
 int /*<<< orphan*/  vprbrd_adc_iio_info ; 

__attribute__((used)) static int vprbrd_adc_probe(struct platform_device *pdev)
{
	struct vprbrd *vb = dev_get_drvdata(pdev->dev.parent);
	struct vprbrd_adc *adc;
	struct iio_dev *indio_dev;
	int ret;

	/* registering iio */
	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*adc));
	if (!indio_dev) {
		dev_err(&pdev->dev, "failed allocating iio device\n");
		return -ENOMEM;
	}

	adc = iio_priv(indio_dev);
	adc->vb = vb;
	indio_dev->name = "viperboard adc";
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->info = &vprbrd_adc_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = vprbrd_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(vprbrd_adc_iio_channels);

	ret = devm_iio_device_register(&pdev->dev, indio_dev);
	if (ret) {
		dev_err(&pdev->dev, "could not register iio (adc)");
		return ret;
	}

	return 0;
}