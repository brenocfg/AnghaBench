#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msm_vibrator {int enabled; TYPE_2__* input; int /*<<< orphan*/  worker; int /*<<< orphan*/  mutex; int /*<<< orphan*/  base; int /*<<< orphan*/  clk; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  vcc; } ;
struct TYPE_7__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_8__ {char* name; int /*<<< orphan*/  close; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct msm_vibrator* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int input_ff_create_memless (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct msm_vibrator*) ; 
 int /*<<< orphan*/  msm_vibrator_close ; 
 int /*<<< orphan*/  msm_vibrator_play_effect ; 
 int /*<<< orphan*/  msm_vibrator_worker ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct msm_vibrator*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int msm_vibrator_probe(struct platform_device *pdev)
{
	struct msm_vibrator *vibrator;
	struct resource *res;
	int ret;

	vibrator = devm_kzalloc(&pdev->dev, sizeof(*vibrator), GFP_KERNEL);
	if (!vibrator)
		return -ENOMEM;

	vibrator->input = devm_input_allocate_device(&pdev->dev);
	if (!vibrator->input)
		return -ENOMEM;

	vibrator->vcc = devm_regulator_get(&pdev->dev, "vcc");
	if (IS_ERR(vibrator->vcc)) {
		if (PTR_ERR(vibrator->vcc) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get regulator: %ld\n",
				PTR_ERR(vibrator->vcc));
		return PTR_ERR(vibrator->vcc);
	}

	vibrator->enable_gpio = devm_gpiod_get(&pdev->dev, "enable",
					       GPIOD_OUT_LOW);
	if (IS_ERR(vibrator->enable_gpio)) {
		if (PTR_ERR(vibrator->enable_gpio) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get enable gpio: %ld\n",
				PTR_ERR(vibrator->enable_gpio));
		return PTR_ERR(vibrator->enable_gpio);
	}

	vibrator->clk = devm_clk_get(&pdev->dev, "pwm");
	if (IS_ERR(vibrator->clk)) {
		if (PTR_ERR(vibrator->clk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to lookup pwm clock: %ld\n",
				PTR_ERR(vibrator->clk));
		return PTR_ERR(vibrator->clk);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get platform resource\n");
		return -ENODEV;
	}

	vibrator->base = devm_ioremap(&pdev->dev, res->start,
				     resource_size(res));
	if (!vibrator->base) {
		dev_err(&pdev->dev, "Failed to iomap resource.\n");
		return -ENOMEM;
	}

	vibrator->enabled = false;
	mutex_init(&vibrator->mutex);
	INIT_WORK(&vibrator->worker, msm_vibrator_worker);

	vibrator->input->name = "msm-vibrator";
	vibrator->input->id.bustype = BUS_HOST;
	vibrator->input->close = msm_vibrator_close;

	input_set_drvdata(vibrator->input, vibrator);
	input_set_capability(vibrator->input, EV_FF, FF_RUMBLE);

	ret = input_ff_create_memless(vibrator->input, NULL,
				      msm_vibrator_play_effect);
	if (ret) {
		dev_err(&pdev->dev, "Failed to create ff memless: %d", ret);
		return ret;
	}

	ret = input_register_device(vibrator->input);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register input device: %d", ret);
		return ret;
	}

	platform_set_drvdata(pdev, vibrator);

	return 0;
}