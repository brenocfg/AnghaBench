#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  parent; scalar_t__ of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct palmas_platform_data {struct palmas_gpadc_platform_data* gpadc_pdata; } ;
struct palmas_gpadc_platform_data {int ch0_current; int ch3_current; scalar_t__ adc_wakeup1_data; scalar_t__ adc_wakeup2_data; int /*<<< orphan*/  extended_delay; int /*<<< orphan*/  auto_conversion_period_ms; } ;
struct palmas_gpadc {int irq; int wakeup1_enable; int irq_auto_0; int wakeup2_enable; int irq_auto_1; TYPE_2__* adc_info; TYPE_3__* dev; int /*<<< orphan*/  extended_delay; int /*<<< orphan*/  ch3_current; int /*<<< orphan*/  ch0_current; int /*<<< orphan*/  wakeup2_data; int /*<<< orphan*/  wakeup1_data; int /*<<< orphan*/  palmas; int /*<<< orphan*/  auto_conversion_period; int /*<<< orphan*/  conv_completion; } ;
struct TYPE_9__ {TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  is_uncalibrated; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  MOD_NAME ; 
 int /*<<< orphan*/  PALMAS_ADC_CH0_CURRENT_SRC_0 ; 
 int /*<<< orphan*/  PALMAS_ADC_CH0_CURRENT_SRC_15 ; 
 int /*<<< orphan*/  PALMAS_ADC_CH0_CURRENT_SRC_20 ; 
 int /*<<< orphan*/  PALMAS_ADC_CH0_CURRENT_SRC_5 ; 
 int /*<<< orphan*/  PALMAS_ADC_CH3_CURRENT_SRC_0 ; 
 int /*<<< orphan*/  PALMAS_ADC_CH3_CURRENT_SRC_10 ; 
 int /*<<< orphan*/  PALMAS_ADC_CH3_CURRENT_SRC_400 ; 
 int /*<<< orphan*/  PALMAS_ADC_CH3_CURRENT_SRC_800 ; 
 int PALMAS_ADC_CH_MAX ; 
 int /*<<< orphan*/  PALMAS_GPADC_EOC_SW_IRQ ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct palmas_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 char* dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_3__*,struct iio_dev*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (TYPE_3__*,int) ; 
 int /*<<< orphan*/  device_wakeup_enable (TYPE_3__*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  free_irq (int,struct palmas_gpadc*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct palmas_gpadc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  palmas_gpadc_calibrate (struct palmas_gpadc*,int) ; 
 int palmas_gpadc_get_adc_dt_data (struct platform_device*,struct palmas_gpadc_platform_data**) ; 
 int /*<<< orphan*/  palmas_gpadc_iio_channel ; 
 int /*<<< orphan*/  palmas_gpadc_iio_info ; 
 TYPE_2__* palmas_gpadc_info ; 
 int /*<<< orphan*/  palmas_gpadc_irq ; 
 int /*<<< orphan*/  palmas_gpadc_irq_auto ; 
 int palmas_irq_get_virq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct palmas_gpadc*) ; 

__attribute__((used)) static int palmas_gpadc_probe(struct platform_device *pdev)
{
	struct palmas_gpadc *adc;
	struct palmas_platform_data *pdata;
	struct palmas_gpadc_platform_data *gpadc_pdata = NULL;
	struct iio_dev *indio_dev;
	int ret, i;

	pdata = dev_get_platdata(pdev->dev.parent);

	if (pdata && pdata->gpadc_pdata)
		gpadc_pdata = pdata->gpadc_pdata;

	if (!gpadc_pdata && pdev->dev.of_node) {
		ret = palmas_gpadc_get_adc_dt_data(pdev, &gpadc_pdata);
		if (ret < 0)
			return ret;
	}
	if (!gpadc_pdata)
		return -EINVAL;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*adc));
	if (!indio_dev) {
		dev_err(&pdev->dev, "iio_device_alloc failed\n");
		return -ENOMEM;
	}

	adc = iio_priv(indio_dev);
	adc->dev = &pdev->dev;
	adc->palmas = dev_get_drvdata(pdev->dev.parent);
	adc->adc_info = palmas_gpadc_info;
	init_completion(&adc->conv_completion);
	dev_set_drvdata(&pdev->dev, indio_dev);

	adc->auto_conversion_period = gpadc_pdata->auto_conversion_period_ms;
	adc->irq = palmas_irq_get_virq(adc->palmas, PALMAS_GPADC_EOC_SW_IRQ);
	if (adc->irq < 0) {
		dev_err(adc->dev,
			"get virq failed: %d\n", adc->irq);
		ret = adc->irq;
		goto out;
	}
	ret = request_threaded_irq(adc->irq, NULL,
		palmas_gpadc_irq,
		IRQF_ONESHOT, dev_name(adc->dev),
		adc);
	if (ret < 0) {
		dev_err(adc->dev,
			"request irq %d failed: %d\n", adc->irq, ret);
		goto out;
	}

	if (gpadc_pdata->adc_wakeup1_data) {
		memcpy(&adc->wakeup1_data, gpadc_pdata->adc_wakeup1_data,
			sizeof(adc->wakeup1_data));
		adc->wakeup1_enable = true;
		adc->irq_auto_0 =  platform_get_irq(pdev, 1);
		ret = request_threaded_irq(adc->irq_auto_0, NULL,
				palmas_gpadc_irq_auto,
				IRQF_ONESHOT,
				"palmas-adc-auto-0", adc);
		if (ret < 0) {
			dev_err(adc->dev, "request auto0 irq %d failed: %d\n",
				adc->irq_auto_0, ret);
			goto out_irq_free;
		}
	}

	if (gpadc_pdata->adc_wakeup2_data) {
		memcpy(&adc->wakeup2_data, gpadc_pdata->adc_wakeup2_data,
				sizeof(adc->wakeup2_data));
		adc->wakeup2_enable = true;
		adc->irq_auto_1 =  platform_get_irq(pdev, 2);
		ret = request_threaded_irq(adc->irq_auto_1, NULL,
				palmas_gpadc_irq_auto,
				IRQF_ONESHOT,
				"palmas-adc-auto-1", adc);
		if (ret < 0) {
			dev_err(adc->dev, "request auto1 irq %d failed: %d\n",
				adc->irq_auto_1, ret);
			goto out_irq_auto0_free;
		}
	}

	/* set the current source 0 (value 0/5/15/20 uA => 0..3) */
	if (gpadc_pdata->ch0_current <= 1)
		adc->ch0_current = PALMAS_ADC_CH0_CURRENT_SRC_0;
	else if (gpadc_pdata->ch0_current <= 5)
		adc->ch0_current = PALMAS_ADC_CH0_CURRENT_SRC_5;
	else if (gpadc_pdata->ch0_current <= 15)
		adc->ch0_current = PALMAS_ADC_CH0_CURRENT_SRC_15;
	else
		adc->ch0_current = PALMAS_ADC_CH0_CURRENT_SRC_20;

	/* set the current source 3 (value 0/10/400/800 uA => 0..3) */
	if (gpadc_pdata->ch3_current <= 1)
		adc->ch3_current = PALMAS_ADC_CH3_CURRENT_SRC_0;
	else if (gpadc_pdata->ch3_current <= 10)
		adc->ch3_current = PALMAS_ADC_CH3_CURRENT_SRC_10;
	else if (gpadc_pdata->ch3_current <= 400)
		adc->ch3_current = PALMAS_ADC_CH3_CURRENT_SRC_400;
	else
		adc->ch3_current = PALMAS_ADC_CH3_CURRENT_SRC_800;

	adc->extended_delay = gpadc_pdata->extended_delay;

	indio_dev->name = MOD_NAME;
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->info = &palmas_gpadc_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = palmas_gpadc_iio_channel;
	indio_dev->num_channels = ARRAY_SIZE(palmas_gpadc_iio_channel);

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(adc->dev, "iio_device_register() failed: %d\n", ret);
		goto out_irq_auto1_free;
	}

	device_set_wakeup_capable(&pdev->dev, 1);
	for (i = 0; i < PALMAS_ADC_CH_MAX; i++) {
		if (!(adc->adc_info[i].is_uncalibrated))
			palmas_gpadc_calibrate(adc, i);
	}

	if (adc->wakeup1_enable || adc->wakeup2_enable)
		device_wakeup_enable(&pdev->dev);

	return 0;

out_irq_auto1_free:
	if (gpadc_pdata->adc_wakeup2_data)
		free_irq(adc->irq_auto_1, adc);
out_irq_auto0_free:
	if (gpadc_pdata->adc_wakeup1_data)
		free_irq(adc->irq_auto_0, adc);
out_irq_free:
	free_irq(adc->irq, adc);
out:
	return ret;
}