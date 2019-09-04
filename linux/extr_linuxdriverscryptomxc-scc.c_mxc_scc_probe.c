#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mxc_scc {scalar_t__ clk; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; struct device* dev; scalar_t__ base; } ;
typedef  enum mxc_scc_state { ____Placeholder_mxc_scc_state } mxc_scc_state ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ SCC_SCM_ERROR_STATUS ; 
 scalar_t__ SCC_SCM_INTR_CTRL ; 
 int SCC_SCM_INTR_CTRL_CLR_INTR ; 
 int SCC_SCM_INTR_CTRL_MASK_INTR ; 
 scalar_t__ SCC_SMN_COMMAND ; 
 int SCC_SMN_COMMAND_CLR_INTR ; 
 int SCC_SMN_COMMAND_EN_INTR ; 
 int SCC_STATE_OK ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 scalar_t__ devm_clk_get (struct device*,char*) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 struct mxc_scc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mxc_scc*) ; 
 int mxc_scc_crypto_register (struct mxc_scc*) ; 
 int mxc_scc_get_config (struct mxc_scc*) ; 
 int mxc_scc_get_state (struct mxc_scc*) ; 
 int /*<<< orphan*/  mxc_scc_hw_init (struct mxc_scc*) ; 
 int /*<<< orphan*/  mxc_scc_int ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mxc_scc*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxc_scc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct mxc_scc *scc;
	enum mxc_scc_state state;
	int irq;
	int ret;
	int i;

	scc = devm_kzalloc(dev, sizeof(*scc), GFP_KERNEL);
	if (!scc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	scc->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(scc->base))
		return PTR_ERR(scc->base);

	scc->clk = devm_clk_get(&pdev->dev, "ipg");
	if (IS_ERR(scc->clk)) {
		dev_err(dev, "Could not get ipg clock\n");
		return PTR_ERR(scc->clk);
	}

	ret = clk_prepare_enable(scc->clk);
	if (ret)
		return ret;

	/* clear error status register */
	writel(0x0, scc->base + SCC_SCM_ERROR_STATUS);

	/* clear interrupt control registers */
	writel(SCC_SCM_INTR_CTRL_CLR_INTR |
	       SCC_SCM_INTR_CTRL_MASK_INTR,
	       scc->base + SCC_SCM_INTR_CTRL);

	writel(SCC_SMN_COMMAND_CLR_INTR |
	       SCC_SMN_COMMAND_EN_INTR,
	       scc->base + SCC_SMN_COMMAND);

	scc->dev = dev;
	platform_set_drvdata(pdev, scc);

	ret = mxc_scc_get_config(scc);
	if (ret)
		goto err_out;

	state = mxc_scc_get_state(scc);

	if (state != SCC_STATE_OK) {
		dev_err(dev, "SCC in unusable state %d\n", state);
		ret = -EINVAL;
		goto err_out;
	}

	mxc_scc_hw_init(scc);

	spin_lock_init(&scc->lock);
	/* FIXME: calculate queue from RAM slots */
	crypto_init_queue(&scc->queue, 50);

	for (i = 0; i < 2; i++) {
		irq = platform_get_irq(pdev, i);
		if (irq < 0) {
			dev_err(dev, "failed to get irq resource: %d\n", irq);
			ret = irq;
			goto err_out;
		}

		ret = devm_request_threaded_irq(dev, irq, NULL, mxc_scc_int,
						IRQF_ONESHOT, dev_name(dev), scc);
		if (ret)
			goto err_out;
	}

	ret = mxc_scc_crypto_register(scc);
	if (ret) {
		dev_err(dev, "could not register algorithms");
		goto err_out;
	}

	dev_info(dev, "registered successfully.\n");

	return 0;

err_out:
	clk_disable_unprepare(scc->clk);

	return ret;
}