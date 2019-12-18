#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_3__ {int base; unsigned int npwm; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct pwm_mediatek_chip {TYPE_1__ chip; TYPE_2__* soc; void** clk_pwms; void* clk_main; void* clk_top; void* regs; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {unsigned int num_pwms; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void** devm_kcalloc (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct pwm_mediatek_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pwm_mediatek_chip*) ; 
 int /*<<< orphan*/  pwm_mediatek_ops ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static int pwm_mediatek_probe(struct platform_device *pdev)
{
	struct pwm_mediatek_chip *pc;
	struct resource *res;
	unsigned int i;
	int ret;

	pc = devm_kzalloc(&pdev->dev, sizeof(*pc), GFP_KERNEL);
	if (!pc)
		return -ENOMEM;

	pc->soc = of_device_get_match_data(&pdev->dev);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pc->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pc->regs))
		return PTR_ERR(pc->regs);

	pc->clk_pwms = devm_kcalloc(&pdev->dev, pc->soc->num_pwms,
				    sizeof(*pc->clk_pwms), GFP_KERNEL);
	if (!pc->clk_pwms)
		return -ENOMEM;

	pc->clk_top = devm_clk_get(&pdev->dev, "top");
	if (IS_ERR(pc->clk_top)) {
		dev_err(&pdev->dev, "clock: top fail: %ld\n",
			PTR_ERR(pc->clk_top));
		return PTR_ERR(pc->clk_top);
	}

	pc->clk_main = devm_clk_get(&pdev->dev, "main");
	if (IS_ERR(pc->clk_main)) {
		dev_err(&pdev->dev, "clock: main fail: %ld\n",
			PTR_ERR(pc->clk_main));
		return PTR_ERR(pc->clk_main);
	}

	for (i = 0; i < pc->soc->num_pwms; i++) {
		char name[8];

		snprintf(name, sizeof(name), "pwm%d", i + 1);

		pc->clk_pwms[i] = devm_clk_get(&pdev->dev, name);
		if (IS_ERR(pc->clk_pwms[i])) {
			dev_err(&pdev->dev, "clock: %s fail: %ld\n",
				name, PTR_ERR(pc->clk_pwms[i]));
			return PTR_ERR(pc->clk_pwms[i]);
		}
	}

	platform_set_drvdata(pdev, pc);

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &pwm_mediatek_ops;
	pc->chip.base = -1;
	pc->chip.npwm = pc->soc->num_pwms;

	ret = pwmchip_add(&pc->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		return ret;
	}

	return 0;
}