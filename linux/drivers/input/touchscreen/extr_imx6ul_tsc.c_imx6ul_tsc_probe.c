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
typedef  int u32 ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; } ;
struct imx6ul_tsc {int measure_delay_time; int pre_charge_time; int average_enable; struct input_dev* input; int /*<<< orphan*/  average_select; TYPE_2__* dev; void* adc_clk; void* tsc_clk; void* adc_regs; void* tsc_regs; void* xnur_gpio; int /*<<< orphan*/  completion; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  adc_irq_fn ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 void* devm_gpiod_get (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 struct input_dev* devm_input_allocate_device (TYPE_2__*) ; 
 struct imx6ul_tsc* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct imx6ul_tsc*) ; 
 int devm_request_threaded_irq (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct imx6ul_tsc*) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  imx6ul_tsc_close ; 
 int /*<<< orphan*/  imx6ul_tsc_open ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct imx6ul_tsc*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx6ul_tsc*) ; 
 int /*<<< orphan*/  tsc_irq_fn ; 

__attribute__((used)) static int imx6ul_tsc_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct imx6ul_tsc *tsc;
	struct input_dev *input_dev;
	int err;
	int tsc_irq;
	int adc_irq;
	u32 average_samples;

	tsc = devm_kzalloc(&pdev->dev, sizeof(*tsc), GFP_KERNEL);
	if (!tsc)
		return -ENOMEM;

	input_dev = devm_input_allocate_device(&pdev->dev);
	if (!input_dev)
		return -ENOMEM;

	input_dev->name = "iMX6UL Touchscreen Controller";
	input_dev->id.bustype = BUS_HOST;

	input_dev->open = imx6ul_tsc_open;
	input_dev->close = imx6ul_tsc_close;

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);
	input_set_abs_params(input_dev, ABS_X, 0, 0xFFF, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, 0xFFF, 0, 0);

	input_set_drvdata(input_dev, tsc);

	tsc->dev = &pdev->dev;
	tsc->input = input_dev;
	init_completion(&tsc->completion);

	tsc->xnur_gpio = devm_gpiod_get(&pdev->dev, "xnur", GPIOD_IN);
	if (IS_ERR(tsc->xnur_gpio)) {
		err = PTR_ERR(tsc->xnur_gpio);
		dev_err(&pdev->dev,
			"failed to request GPIO tsc_X- (xnur): %d\n", err);
		return err;
	}

	tsc->tsc_regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(tsc->tsc_regs)) {
		err = PTR_ERR(tsc->tsc_regs);
		dev_err(&pdev->dev, "failed to remap tsc memory: %d\n", err);
		return err;
	}

	tsc->adc_regs = devm_platform_ioremap_resource(pdev, 1);
	if (IS_ERR(tsc->adc_regs)) {
		err = PTR_ERR(tsc->adc_regs);
		dev_err(&pdev->dev, "failed to remap adc memory: %d\n", err);
		return err;
	}

	tsc->tsc_clk = devm_clk_get(&pdev->dev, "tsc");
	if (IS_ERR(tsc->tsc_clk)) {
		err = PTR_ERR(tsc->tsc_clk);
		dev_err(&pdev->dev, "failed getting tsc clock: %d\n", err);
		return err;
	}

	tsc->adc_clk = devm_clk_get(&pdev->dev, "adc");
	if (IS_ERR(tsc->adc_clk)) {
		err = PTR_ERR(tsc->adc_clk);
		dev_err(&pdev->dev, "failed getting adc clock: %d\n", err);
		return err;
	}

	tsc_irq = platform_get_irq(pdev, 0);
	if (tsc_irq < 0)
		return tsc_irq;

	adc_irq = platform_get_irq(pdev, 1);
	if (adc_irq < 0)
		return adc_irq;

	err = devm_request_threaded_irq(tsc->dev, tsc_irq,
					NULL, tsc_irq_fn, IRQF_ONESHOT,
					dev_name(&pdev->dev), tsc);
	if (err) {
		dev_err(&pdev->dev,
			"failed requesting tsc irq %d: %d\n",
			tsc_irq, err);
		return err;
	}

	err = devm_request_irq(tsc->dev, adc_irq, adc_irq_fn, 0,
				dev_name(&pdev->dev), tsc);
	if (err) {
		dev_err(&pdev->dev,
			"failed requesting adc irq %d: %d\n",
			adc_irq, err);
		return err;
	}

	err = of_property_read_u32(np, "measure-delay-time",
				   &tsc->measure_delay_time);
	if (err)
		tsc->measure_delay_time = 0xffff;

	err = of_property_read_u32(np, "pre-charge-time",
				   &tsc->pre_charge_time);
	if (err)
		tsc->pre_charge_time = 0xfff;

	err = of_property_read_u32(np, "touchscreen-average-samples",
				   &average_samples);
	if (err)
		average_samples = 1;

	switch (average_samples) {
	case 1:
		tsc->average_enable = false;
		tsc->average_select = 0; /* value unused; initialize anyway */
		break;
	case 4:
	case 8:
	case 16:
	case 32:
		tsc->average_enable = true;
		tsc->average_select = ilog2(average_samples) - 2;
		break;
	default:
		dev_err(&pdev->dev,
			"touchscreen-average-samples (%u) must be 1, 4, 8, 16 or 32\n",
			average_samples);
		return -EINVAL;
	}

	err = input_register_device(tsc->input);
	if (err) {
		dev_err(&pdev->dev,
			"failed to register input device: %d\n", err);
		return err;
	}

	platform_set_drvdata(pdev, tsc);
	return 0;
}