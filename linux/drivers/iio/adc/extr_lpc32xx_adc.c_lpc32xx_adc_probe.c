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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct lpc32xx_adc_state {int /*<<< orphan*/  completion; int /*<<< orphan*/  vref; int /*<<< orphan*/  clk; int /*<<< orphan*/  adc_base; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC32XXAD_NAME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpc32xx_adc_state*) ; 
 struct lpc32xx_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpc32xx_adc_iio_channels ; 
 int /*<<< orphan*/  lpc32xx_adc_iio_info ; 
 int /*<<< orphan*/  lpc32xx_adc_iio_scale_channels ; 
 int /*<<< orphan*/  lpc32xx_adc_isr ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int lpc32xx_adc_probe(struct platform_device *pdev)
{
	struct lpc32xx_adc_state *st = NULL;
	struct resource *res;
	int retval = -ENODEV;
	struct iio_dev *iodev = NULL;
	int irq;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "failed to get platform I/O memory\n");
		return -ENXIO;
	}

	iodev = devm_iio_device_alloc(&pdev->dev, sizeof(*st));
	if (!iodev)
		return -ENOMEM;

	st = iio_priv(iodev);

	st->adc_base = devm_ioremap(&pdev->dev, res->start,
				    resource_size(res));
	if (!st->adc_base) {
		dev_err(&pdev->dev, "failed mapping memory\n");
		return -EBUSY;
	}

	st->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(st->clk)) {
		dev_err(&pdev->dev, "failed getting clock\n");
		return PTR_ERR(st->clk);
	}

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return -ENXIO;

	retval = devm_request_irq(&pdev->dev, irq, lpc32xx_adc_isr, 0,
				  LPC32XXAD_NAME, st);
	if (retval < 0) {
		dev_err(&pdev->dev, "failed requesting interrupt\n");
		return retval;
	}

	st->vref = devm_regulator_get(&pdev->dev, "vref");
	if (IS_ERR(st->vref)) {
		iodev->channels = lpc32xx_adc_iio_channels;
		dev_info(&pdev->dev,
			 "Missing vref regulator: No scaling available\n");
	} else {
		iodev->channels = lpc32xx_adc_iio_scale_channels;
	}

	platform_set_drvdata(pdev, iodev);

	init_completion(&st->completion);

	iodev->name = LPC32XXAD_NAME;
	iodev->dev.parent = &pdev->dev;
	iodev->info = &lpc32xx_adc_iio_info;
	iodev->modes = INDIO_DIRECT_MODE;
	iodev->num_channels = ARRAY_SIZE(lpc32xx_adc_iio_channels);

	retval = devm_iio_device_register(&pdev->dev, iodev);
	if (retval)
		return retval;

	dev_info(&pdev->dev, "LPC32XX ADC driver loaded, IRQ %d\n", irq);

	return 0;
}