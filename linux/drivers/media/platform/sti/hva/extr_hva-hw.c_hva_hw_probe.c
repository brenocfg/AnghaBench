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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct hva_dev {int irq_its; int irq_err; scalar_t__ ip_version; int /*<<< orphan*/  clk; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  protect_mutex; int /*<<< orphan*/  esram_size; int /*<<< orphan*/  esram_addr; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOSUSPEND_DELAY_MS ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ERR_PTR (int) ; 
 int /*<<< orphan*/  HVA_PREFIX ; 
 scalar_t__ HVA_VERSION_UNKNOWN ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct hva_dev*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int /*<<< orphan*/  hva_hw_err_interrupt ; 
 int /*<<< orphan*/  hva_hw_err_irq_thread ; 
 scalar_t__ hva_hw_get_ip_version (struct hva_dev*) ; 
 int /*<<< orphan*/  hva_hw_its_interrupt ; 
 int /*<<< orphan*/  hva_hw_its_irq_thread ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

int hva_hw_probe(struct platform_device *pdev, struct hva_dev *hva)
{
	struct device *dev = &pdev->dev;
	struct resource *regs;
	struct resource *esram;
	int ret;

	WARN_ON(!hva);

	/* get memory for registers */
	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hva->regs = devm_ioremap_resource(dev, regs);
	if (IS_ERR(hva->regs)) {
		dev_err(dev, "%s     failed to get regs\n", HVA_PREFIX);
		return PTR_ERR(hva->regs);
	}

	/* get memory for esram */
	esram = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!esram) {
		dev_err(dev, "%s     failed to get esram\n", HVA_PREFIX);
		return -ENODEV;
	}
	hva->esram_addr = esram->start;
	hva->esram_size = resource_size(esram);

	dev_info(dev, "%s     esram reserved for address: 0x%x size:%d\n",
		 HVA_PREFIX, hva->esram_addr, hva->esram_size);

	/* get clock resource */
	hva->clk = devm_clk_get(dev, "clk_hva");
	if (IS_ERR(hva->clk)) {
		dev_err(dev, "%s     failed to get clock\n", HVA_PREFIX);
		return PTR_ERR(hva->clk);
	}

	ret = clk_prepare(hva->clk);
	if (ret < 0) {
		dev_err(dev, "%s     failed to prepare clock\n", HVA_PREFIX);
		hva->clk = ERR_PTR(-EINVAL);
		return ret;
	}

	/* get status interruption resource */
	ret  = platform_get_irq(pdev, 0);
	if (ret < 0)
		goto err_clk;
	hva->irq_its = ret;

	ret = devm_request_threaded_irq(dev, hva->irq_its, hva_hw_its_interrupt,
					hva_hw_its_irq_thread,
					IRQF_ONESHOT,
					"hva_its_irq", hva);
	if (ret) {
		dev_err(dev, "%s     failed to install status IRQ 0x%x\n",
			HVA_PREFIX, hva->irq_its);
		goto err_clk;
	}
	disable_irq(hva->irq_its);

	/* get error interruption resource */
	ret = platform_get_irq(pdev, 1);
	if (ret < 0)
		goto err_clk;
	hva->irq_err = ret;

	ret = devm_request_threaded_irq(dev, hva->irq_err, hva_hw_err_interrupt,
					hva_hw_err_irq_thread,
					IRQF_ONESHOT,
					"hva_err_irq", hva);
	if (ret) {
		dev_err(dev, "%s     failed to install error IRQ 0x%x\n",
			HVA_PREFIX, hva->irq_err);
		goto err_clk;
	}
	disable_irq(hva->irq_err);

	/* initialise protection mutex */
	mutex_init(&hva->protect_mutex);

	/* initialise completion signal */
	init_completion(&hva->interrupt);

	/* initialise runtime power management */
	pm_runtime_set_autosuspend_delay(dev, AUTOSUSPEND_DELAY_MS);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_suspended(dev);
	pm_runtime_enable(dev);

	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		dev_err(dev, "%s     failed to set PM\n", HVA_PREFIX);
		goto err_clk;
	}

	/* check IP hardware version */
	hva->ip_version = hva_hw_get_ip_version(hva);

	if (hva->ip_version == HVA_VERSION_UNKNOWN) {
		ret = -EINVAL;
		goto err_pm;
	}

	dev_info(dev, "%s     found hva device (version 0x%lx)\n", HVA_PREFIX,
		 hva->ip_version);

	return 0;

err_pm:
	pm_runtime_put(dev);
err_clk:
	if (hva->clk)
		clk_unprepare(hva->clk);

	return ret;
}