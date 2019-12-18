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
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  nr_resets; } ;
struct meson_audio_arb_data {TYPE_1__ rstc; int /*<<< orphan*/  regs; int /*<<< orphan*/  clk; int /*<<< orphan*/  reset_bits; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_GENERAL_BIT ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  axg_audio_arb_reset_bits ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct meson_audio_arb_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  meson_audio_arb_remove (struct platform_device*) ; 
 int /*<<< orphan*/  meson_audio_arb_rstc_ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_audio_arb_data*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_audio_arb_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct meson_audio_arb_data *arb;
	struct resource *res;
	int ret;

	arb = devm_kzalloc(dev, sizeof(*arb), GFP_KERNEL);
	if (!arb)
		return -ENOMEM;
	platform_set_drvdata(pdev, arb);

	arb->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(arb->clk)) {
		if (PTR_ERR(arb->clk) != -EPROBE_DEFER)
			dev_err(dev, "failed to get clock\n");
		return PTR_ERR(arb->clk);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	arb->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(arb->regs))
		return PTR_ERR(arb->regs);

	spin_lock_init(&arb->lock);
	arb->reset_bits = axg_audio_arb_reset_bits;
	arb->rstc.nr_resets = ARRAY_SIZE(axg_audio_arb_reset_bits);
	arb->rstc.ops = &meson_audio_arb_rstc_ops;
	arb->rstc.of_node = dev->of_node;
	arb->rstc.owner = THIS_MODULE;

	/*
	 * Enable general :
	 * In the initial state, all memory interfaces are disabled
	 * and the general bit is on
	 */
	ret = clk_prepare_enable(arb->clk);
	if (ret) {
		dev_err(dev, "failed to enable arb clock\n");
		return ret;
	}
	writel(BIT(ARB_GENERAL_BIT), arb->regs);

	/* Register reset controller */
	ret = devm_reset_controller_register(dev, &arb->rstc);
	if (ret) {
		dev_err(dev, "failed to register arb reset controller\n");
		meson_audio_arb_remove(pdev);
	}

	return ret;
}