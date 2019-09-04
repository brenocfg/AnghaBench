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
struct mtk_cec {int irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct mtk_cec* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct device*) ; 
 int /*<<< orphan*/  mtk_cec_htplg_irq_enable (struct mtk_cec*) ; 
 int /*<<< orphan*/  mtk_cec_htplg_irq_init (struct mtk_cec*) ; 
 int /*<<< orphan*/  mtk_cec_htplg_isr_thread ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_cec*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_cec_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mtk_cec *cec;
	struct resource *res;
	int ret;

	cec = devm_kzalloc(dev, sizeof(*cec), GFP_KERNEL);
	if (!cec)
		return -ENOMEM;

	platform_set_drvdata(pdev, cec);
	spin_lock_init(&cec->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	cec->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(cec->regs)) {
		ret = PTR_ERR(cec->regs);
		dev_err(dev, "Failed to ioremap cec: %d\n", ret);
		return ret;
	}

	cec->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(cec->clk)) {
		ret = PTR_ERR(cec->clk);
		dev_err(dev, "Failed to get cec clock: %d\n", ret);
		return ret;
	}

	cec->irq = platform_get_irq(pdev, 0);
	if (cec->irq < 0) {
		dev_err(dev, "Failed to get cec irq: %d\n", cec->irq);
		return cec->irq;
	}

	ret = devm_request_threaded_irq(dev, cec->irq, NULL,
					mtk_cec_htplg_isr_thread,
					IRQF_SHARED | IRQF_TRIGGER_LOW |
					IRQF_ONESHOT, "hdmi hpd", dev);
	if (ret) {
		dev_err(dev, "Failed to register cec irq: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(cec->clk);
	if (ret) {
		dev_err(dev, "Failed to enable cec clock: %d\n", ret);
		return ret;
	}

	mtk_cec_htplg_irq_init(cec);
	mtk_cec_htplg_irq_enable(cec);

	return 0;
}