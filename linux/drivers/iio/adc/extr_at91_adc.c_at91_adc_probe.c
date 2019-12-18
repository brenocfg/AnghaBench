#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_15__ {TYPE_2__* driver; scalar_t__ of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct TYPE_11__ {TYPE_5__* parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct at91_adc_state {scalar_t__ irq; unsigned int sample_hold_time; void* clk; void* adc_clk; int /*<<< orphan*/  touchscreen_type; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq_data_avail; scalar_t__ sleep_mode; scalar_t__ low_res; TYPE_4__* registers; int /*<<< orphan*/  startup_time; TYPE_3__* caps; void* reg_base; } ;
struct TYPE_14__ {int mr_prescal_mask; int mr_startup_mask; } ;
struct TYPE_13__ {unsigned int (* calc_startup_ticks ) (int /*<<< orphan*/ ,unsigned int) ;scalar_t__ has_tsmr; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_ADC_CR ; 
 int /*<<< orphan*/  AT91_ADC_IDR ; 
 int AT91_ADC_LOWRES ; 
 int /*<<< orphan*/  AT91_ADC_MR ; 
 int AT91_ADC_PRESCAL_ (unsigned int) ; 
 int AT91_ADC_SHTIM ; 
 int AT91_ADC_SHTIM_ (unsigned int) ; 
 int AT91_ADC_SLEEP ; 
 int AT91_ADC_STARTUP_ (unsigned int) ; 
 int AT91_ADC_SWRST ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  at91_adc_9x5_interrupt ; 
 int at91_adc_buffer_init (struct iio_dev*) ; 
 int /*<<< orphan*/  at91_adc_buffer_remove (struct iio_dev*) ; 
 int at91_adc_channel_init (struct iio_dev*) ; 
 int /*<<< orphan*/  at91_adc_info ; 
 int at91_adc_probe_dt (struct at91_adc_state*,struct platform_device*) ; 
 int at91_adc_probe_pdata (struct at91_adc_state*,struct platform_device*) ; 
 int /*<<< orphan*/  at91_adc_rl_interrupt ; 
 int at91_adc_trigger_init (struct iio_dev*) ; 
 int /*<<< orphan*/  at91_adc_trigger_remove (struct iio_dev*) ; 
 int /*<<< orphan*/  at91_adc_writel (struct at91_adc_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  at91_ts_hw_init (struct at91_adc_state*,unsigned int) ; 
 int at91_ts_register (struct at91_adc_state*,struct platform_device*) ; 
 int /*<<< orphan*/  at91_ts_unregister (struct at91_adc_state*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 unsigned int clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_5__*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_5__*) ; 
 void* devm_clk_get (TYPE_5__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_5__*,int) ; 
 void* devm_ioremap_resource (TYPE_5__*,struct resource*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iio_dev*) ; 
 unsigned int round_up (unsigned int,int) ; 
 unsigned int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int at91_adc_probe(struct platform_device *pdev)
{
	unsigned int prsc, mstrclk, ticks, adc_clk, adc_clk_khz, shtim;
	int ret;
	struct iio_dev *idev;
	struct at91_adc_state *st;
	struct resource *res;
	u32 reg;

	idev = devm_iio_device_alloc(&pdev->dev, sizeof(struct at91_adc_state));
	if (!idev)
		return -ENOMEM;

	st = iio_priv(idev);

	if (pdev->dev.of_node)
		ret = at91_adc_probe_dt(st, pdev);
	else
		ret = at91_adc_probe_pdata(st, pdev);

	if (ret) {
		dev_err(&pdev->dev, "No platform data available.\n");
		return -EINVAL;
	}

	platform_set_drvdata(pdev, idev);

	idev->dev.parent = &pdev->dev;
	idev->name = dev_name(&pdev->dev);
	idev->modes = INDIO_DIRECT_MODE;
	idev->info = &at91_adc_info;

	st->irq = platform_get_irq(pdev, 0);
	if (st->irq < 0)
		return -ENODEV;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	st->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(st->reg_base))
		return PTR_ERR(st->reg_base);


	/*
	 * Disable all IRQs before setting up the handler
	 */
	at91_adc_writel(st, AT91_ADC_CR, AT91_ADC_SWRST);
	at91_adc_writel(st, AT91_ADC_IDR, 0xFFFFFFFF);

	if (st->caps->has_tsmr)
		ret = request_irq(st->irq, at91_adc_9x5_interrupt, 0,
				  pdev->dev.driver->name, idev);
	else
		ret = request_irq(st->irq, at91_adc_rl_interrupt, 0,
				  pdev->dev.driver->name, idev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to allocate IRQ.\n");
		return ret;
	}

	st->clk = devm_clk_get(&pdev->dev, "adc_clk");
	if (IS_ERR(st->clk)) {
		dev_err(&pdev->dev, "Failed to get the clock.\n");
		ret = PTR_ERR(st->clk);
		goto error_free_irq;
	}

	ret = clk_prepare_enable(st->clk);
	if (ret) {
		dev_err(&pdev->dev,
			"Could not prepare or enable the clock.\n");
		goto error_free_irq;
	}

	st->adc_clk = devm_clk_get(&pdev->dev, "adc_op_clk");
	if (IS_ERR(st->adc_clk)) {
		dev_err(&pdev->dev, "Failed to get the ADC clock.\n");
		ret = PTR_ERR(st->adc_clk);
		goto error_disable_clk;
	}

	ret = clk_prepare_enable(st->adc_clk);
	if (ret) {
		dev_err(&pdev->dev,
			"Could not prepare or enable the ADC clock.\n");
		goto error_disable_clk;
	}

	/*
	 * Prescaler rate computation using the formula from the Atmel's
	 * datasheet : ADC Clock = MCK / ((Prescaler + 1) * 2), ADC Clock being
	 * specified by the electrical characteristics of the board.
	 */
	mstrclk = clk_get_rate(st->clk);
	adc_clk = clk_get_rate(st->adc_clk);
	adc_clk_khz = adc_clk / 1000;

	dev_dbg(&pdev->dev, "Master clock is set as: %d Hz, adc_clk should set as: %d Hz\n",
		mstrclk, adc_clk);

	prsc = (mstrclk / (2 * adc_clk)) - 1;

	if (!st->startup_time) {
		dev_err(&pdev->dev, "No startup time available.\n");
		ret = -EINVAL;
		goto error_disable_adc_clk;
	}
	ticks = (*st->caps->calc_startup_ticks)(st->startup_time, adc_clk_khz);

	/*
	 * a minimal Sample and Hold Time is necessary for the ADC to guarantee
	 * the best converted final value between two channels selection
	 * The formula thus is : Sample and Hold Time = (shtim + 1) / ADCClock
	 */
	if (st->sample_hold_time > 0)
		shtim = round_up((st->sample_hold_time * adc_clk_khz / 1000)
				 - 1, 1);
	else
		shtim = 0;

	reg = AT91_ADC_PRESCAL_(prsc) & st->registers->mr_prescal_mask;
	reg |= AT91_ADC_STARTUP_(ticks) & st->registers->mr_startup_mask;
	if (st->low_res)
		reg |= AT91_ADC_LOWRES;
	if (st->sleep_mode)
		reg |= AT91_ADC_SLEEP;
	reg |= AT91_ADC_SHTIM_(shtim) & AT91_ADC_SHTIM;
	at91_adc_writel(st, AT91_ADC_MR, reg);

	/* Setup the ADC channels available on the board */
	ret = at91_adc_channel_init(idev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Couldn't initialize the channels.\n");
		goto error_disable_adc_clk;
	}

	init_waitqueue_head(&st->wq_data_avail);
	mutex_init(&st->lock);

	/*
	 * Since touch screen will set trigger register as period trigger. So
	 * when touch screen is enabled, then we have to disable hardware
	 * trigger for classic adc.
	 */
	if (!st->touchscreen_type) {
		ret = at91_adc_buffer_init(idev);
		if (ret < 0) {
			dev_err(&pdev->dev, "Couldn't initialize the buffer.\n");
			goto error_disable_adc_clk;
		}

		ret = at91_adc_trigger_init(idev);
		if (ret < 0) {
			dev_err(&pdev->dev, "Couldn't setup the triggers.\n");
			at91_adc_buffer_remove(idev);
			goto error_disable_adc_clk;
		}
	} else {
		ret = at91_ts_register(st, pdev);
		if (ret)
			goto error_disable_adc_clk;

		at91_ts_hw_init(st, adc_clk_khz);
	}

	ret = iio_device_register(idev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Couldn't register the device.\n");
		goto error_iio_device_register;
	}

	return 0;

error_iio_device_register:
	if (!st->touchscreen_type) {
		at91_adc_trigger_remove(idev);
		at91_adc_buffer_remove(idev);
	} else {
		at91_ts_unregister(st);
	}
error_disable_adc_clk:
	clk_disable_unprepare(st->adc_clk);
error_disable_clk:
	clk_disable_unprepare(st->clk);
error_free_irq:
	free_irq(st->irq, idev);
	return ret;
}