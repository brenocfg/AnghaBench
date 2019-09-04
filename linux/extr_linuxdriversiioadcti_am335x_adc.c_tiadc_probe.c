#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tiadc_device {TYPE_2__* mfd_tscadc; int /*<<< orphan*/  channels; int /*<<< orphan*/  fifo1_lock; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_6__ {TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  FIFO1_THRESHOLD ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  REG_FIFO1THR ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct tiadc_device* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 TYPE_2__* ti_tscadc_dev_get (struct platform_device*) ; 
 int /*<<< orphan*/  tiadc_buffer_setup_ops ; 
 int tiadc_channel_init (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tiadc_channels_remove (struct iio_dev*) ; 
 int /*<<< orphan*/  tiadc_iio_buffered_hardware_remove (struct iio_dev*) ; 
 int tiadc_iio_buffered_hardware_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tiadc_info ; 
 int /*<<< orphan*/  tiadc_irq_h ; 
 int /*<<< orphan*/  tiadc_parse_dt (struct platform_device*,struct tiadc_device*) ; 
 int tiadc_request_dma (struct platform_device*,struct tiadc_device*) ; 
 int /*<<< orphan*/  tiadc_step_config (struct iio_dev*) ; 
 int /*<<< orphan*/  tiadc_worker_h ; 
 int /*<<< orphan*/  tiadc_writel (struct tiadc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tiadc_probe(struct platform_device *pdev)
{
	struct iio_dev		*indio_dev;
	struct tiadc_device	*adc_dev;
	struct device_node	*node = pdev->dev.of_node;
	int			err;

	if (!node) {
		dev_err(&pdev->dev, "Could not find valid DT data.\n");
		return -EINVAL;
	}

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*adc_dev));
	if (indio_dev == NULL) {
		dev_err(&pdev->dev, "failed to allocate iio device\n");
		return -ENOMEM;
	}
	adc_dev = iio_priv(indio_dev);

	adc_dev->mfd_tscadc = ti_tscadc_dev_get(pdev);
	tiadc_parse_dt(pdev, adc_dev);

	indio_dev->dev.parent = &pdev->dev;
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &tiadc_info;

	tiadc_step_config(indio_dev);
	tiadc_writel(adc_dev, REG_FIFO1THR, FIFO1_THRESHOLD);
	mutex_init(&adc_dev->fifo1_lock);

	err = tiadc_channel_init(indio_dev, adc_dev->channels);
	if (err < 0)
		return err;

	err = tiadc_iio_buffered_hardware_setup(indio_dev,
		&tiadc_worker_h,
		&tiadc_irq_h,
		adc_dev->mfd_tscadc->irq,
		IRQF_SHARED,
		&tiadc_buffer_setup_ops);

	if (err)
		goto err_free_channels;

	err = iio_device_register(indio_dev);
	if (err)
		goto err_buffer_unregister;

	platform_set_drvdata(pdev, indio_dev);

	err = tiadc_request_dma(pdev, adc_dev);
	if (err && err == -EPROBE_DEFER)
		goto err_dma;

	return 0;

err_dma:
	iio_device_unregister(indio_dev);
err_buffer_unregister:
	tiadc_iio_buffered_hardware_remove(indio_dev);
err_free_channels:
	tiadc_channels_remove(indio_dev);
	return err;
}