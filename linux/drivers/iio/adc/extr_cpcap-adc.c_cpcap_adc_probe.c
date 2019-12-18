#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct iio_dev {int modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct cpcap_adc {scalar_t__ irq; int /*<<< orphan*/  vendor; int /*<<< orphan*/  reg; TYPE_2__* dev; int /*<<< orphan*/  wq_data_avail; int /*<<< orphan*/  lock; scalar_t__ ato; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int INDIO_BUFFER_SOFTWARE ; 
 int INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IRQF_TRIGGER_NONE ; 
 int cpcap_adc_calibrate (struct cpcap_adc*) ; 
 int /*<<< orphan*/  cpcap_adc_channels ; 
 int /*<<< orphan*/  cpcap_adc_id_table ; 
 int /*<<< orphan*/  cpcap_adc_info ; 
 int /*<<< orphan*/  cpcap_adc_irq_thread ; 
 int cpcap_get_vendor (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_iio_device_register (TYPE_2__*,struct iio_dev*) ; 
 int devm_request_threaded_irq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct iio_dev*) ; 
 struct cpcap_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 

__attribute__((used)) static int cpcap_adc_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct cpcap_adc *ddata;
	struct iio_dev *indio_dev;
	int error;

	match = of_match_device(of_match_ptr(cpcap_adc_id_table),
				&pdev->dev);
	if (!match)
		return -EINVAL;

	if (!match->data) {
		dev_err(&pdev->dev, "no configuration data found\n");

		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*ddata));
	if (!indio_dev) {
		dev_err(&pdev->dev, "failed to allocate iio device\n");

		return -ENOMEM;
	}
	ddata = iio_priv(indio_dev);
	ddata->ato = match->data;
	ddata->dev = &pdev->dev;

	mutex_init(&ddata->lock);
	init_waitqueue_head(&ddata->wq_data_avail);

	indio_dev->modes = INDIO_DIRECT_MODE | INDIO_BUFFER_SOFTWARE;
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->channels = cpcap_adc_channels;
	indio_dev->num_channels = ARRAY_SIZE(cpcap_adc_channels);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &cpcap_adc_info;

	ddata->reg = dev_get_regmap(pdev->dev.parent, NULL);
	if (!ddata->reg)
		return -ENODEV;

	error = cpcap_get_vendor(ddata->dev, ddata->reg, &ddata->vendor);
	if (error)
		return error;

	platform_set_drvdata(pdev, indio_dev);

	ddata->irq = platform_get_irq_byname(pdev, "adcdone");
	if (ddata->irq < 0)
		return -ENODEV;

	error = devm_request_threaded_irq(&pdev->dev, ddata->irq, NULL,
					  cpcap_adc_irq_thread,
					  IRQF_TRIGGER_NONE,
					  "cpcap-adc", indio_dev);
	if (error) {
		dev_err(&pdev->dev, "could not get irq: %i\n",
			error);

		return error;
	}

	error = cpcap_adc_calibrate(ddata);
	if (error)
		return error;

	dev_info(&pdev->dev, "CPCAP ADC device probed\n");

	return devm_iio_device_register(&pdev->dev, indio_dev);
}