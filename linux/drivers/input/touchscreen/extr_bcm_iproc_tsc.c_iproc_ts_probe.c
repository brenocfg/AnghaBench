#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  fuzz_y; int /*<<< orphan*/  max_y; int /*<<< orphan*/  fuzz_x; int /*<<< orphan*/  max_x; } ;
struct iproc_ts_priv {struct input_dev* idev; TYPE_3__ cfg_params; int /*<<< orphan*/  pen_status; struct platform_device* pdev; int /*<<< orphan*/  tsc_clk; int /*<<< orphan*/  regmap; } ;
struct TYPE_11__ {scalar_t__ version; scalar_t__ product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct TYPE_10__ {TYPE_4__* parent; } ;
struct input_dev {int* evbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  keybit; TYPE_2__ id; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPROC_TS_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PEN_UP_STATUS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERIO_UNKNOWN ; 
 int /*<<< orphan*/  X_MIN ; 
 int /*<<< orphan*/  Y_MIN ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_4__*,char*) ; 
 struct input_dev* devm_input_allocate_device (TYPE_4__*) ; 
 struct iproc_ts_priv* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct iproc_ts_priv*) ; 
 int iproc_get_tsc_config (TYPE_4__*,struct iproc_ts_priv*) ; 
 int /*<<< orphan*/  iproc_touchscreen_interrupt ; 
 int /*<<< orphan*/  iproc_ts_start ; 
 int /*<<< orphan*/  iproc_ts_stop ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iproc_ts_priv*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int iproc_ts_probe(struct platform_device *pdev)
{
	struct iproc_ts_priv *priv;
	struct input_dev *idev;
	int irq;
	int error;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	/* touchscreen controller memory mapped regs via syscon*/
	priv->regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							"ts_syscon");
	if (IS_ERR(priv->regmap)) {
		error = PTR_ERR(priv->regmap);
		dev_err(&pdev->dev, "unable to map I/O memory:%d\n", error);
		return error;
	}

	priv->tsc_clk = devm_clk_get(&pdev->dev, "tsc_clk");
	if (IS_ERR(priv->tsc_clk)) {
		error = PTR_ERR(priv->tsc_clk);
		dev_err(&pdev->dev,
			"failed getting clock tsc_clk: %d\n", error);
		return error;
	}

	priv->pdev = pdev;
	error = iproc_get_tsc_config(&pdev->dev, priv);
	if (error) {
		dev_err(&pdev->dev, "get_tsc_config failed: %d\n", error);
		return error;
	}

	idev = devm_input_allocate_device(&pdev->dev);
	if (!idev) {
		dev_err(&pdev->dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	priv->idev = idev;
	priv->pen_status = PEN_UP_STATUS;

	/* Set input device info  */
	idev->name = IPROC_TS_NAME;
	idev->dev.parent = &pdev->dev;

	idev->id.bustype = BUS_HOST;
	idev->id.vendor = SERIO_UNKNOWN;
	idev->id.product = 0;
	idev->id.version = 0;

	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	__set_bit(BTN_TOUCH, idev->keybit);

	input_set_abs_params(idev, ABS_X, X_MIN, priv->cfg_params.max_x,
			     priv->cfg_params.fuzz_x, 0);
	input_set_abs_params(idev, ABS_Y, Y_MIN, priv->cfg_params.max_y,
			     priv->cfg_params.fuzz_y, 0);

	idev->open = iproc_ts_start;
	idev->close = iproc_ts_stop;

	input_set_drvdata(idev, priv);
	platform_set_drvdata(pdev, priv);

	/* get interrupt */
	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	error = devm_request_irq(&pdev->dev, irq,
				 iproc_touchscreen_interrupt,
				 IRQF_SHARED, IPROC_TS_NAME, pdev);
	if (error)
		return error;

	error = input_register_device(priv->idev);
	if (error) {
		dev_err(&pdev->dev,
			"failed to register input device: %d\n", error);
		return error;
	}

	return 0;
}