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
struct z188_adc {struct resource* mem; int /*<<< orphan*/ * base; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct mcb_device_id {int dummy; } ;
struct mcb_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {char* name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (struct resource*) ; 
 int PTR_ERR (struct resource*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct z188_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcb_release_mem (struct resource*) ; 
 struct resource* mcb_request_mem (struct mcb_device*,char*) ; 
 int /*<<< orphan*/  mcb_set_drvdata (struct mcb_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  men_z188_config_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  z188_adc_iio_channels ; 
 int /*<<< orphan*/  z188_adc_info ; 

__attribute__((used)) static int men_z188_probe(struct mcb_device *dev,
			const struct mcb_device_id *id)
{
	struct z188_adc *adc;
	struct iio_dev *indio_dev;
	struct resource *mem;

	indio_dev = devm_iio_device_alloc(&dev->dev, sizeof(struct z188_adc));
	if (!indio_dev)
		return -ENOMEM;

	adc = iio_priv(indio_dev);
	indio_dev->name = "z188-adc";
	indio_dev->dev.parent = &dev->dev;
	indio_dev->info = &z188_adc_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = z188_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(z188_adc_iio_channels);

	mem = mcb_request_mem(dev, "z188-adc");
	if (IS_ERR(mem))
		return PTR_ERR(mem);

	adc->base = ioremap(mem->start, resource_size(mem));
	if (adc->base == NULL)
		goto err;

	men_z188_config_channels(adc->base);

	adc->mem = mem;
	mcb_set_drvdata(dev, indio_dev);

	return iio_device_register(indio_dev);

err:
	mcb_release_mem(mem);
	return -ENXIO;
}