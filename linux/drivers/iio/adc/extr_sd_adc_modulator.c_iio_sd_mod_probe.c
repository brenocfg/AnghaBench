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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/ * channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_BUFFER_HARDWARE ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int /*<<< orphan*/ ) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_sd_mod_ch ; 
 int /*<<< orphan*/  iio_sd_mod_iio_info ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 

__attribute__((used)) static int iio_sd_mod_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct iio_dev *iio;

	iio = devm_iio_device_alloc(dev, 0);
	if (!iio)
		return -ENOMEM;

	iio->dev.parent = dev;
	iio->dev.of_node = dev->of_node;
	iio->name = dev_name(dev);
	iio->info = &iio_sd_mod_iio_info;
	iio->modes = INDIO_BUFFER_HARDWARE;

	iio->num_channels = 1;
	iio->channels = &iio_sd_mod_ch;

	platform_set_drvdata(pdev, iio);

	return devm_iio_device_register(&pdev->dev, iio);
}