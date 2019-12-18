#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_5__ {int /*<<< orphan*/ * sram; int /*<<< orphan*/  statf_h; int /*<<< orphan*/  statne_h; int /*<<< orphan*/ * irqen; int /*<<< orphan*/ * irqstat; int /*<<< orphan*/ * stat2; int /*<<< orphan*/ * irqsrc; int /*<<< orphan*/ * stat1; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int QUEUES ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_is_ixp42x_rev_a0 () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 TYPE_1__* devm_ioremap_resource (struct device*,struct resource*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmgr_irq ; 
 int /*<<< orphan*/  qmgr_irq1_a0 ; 
 int /*<<< orphan*/  qmgr_irq2_a0 ; 
 int qmgr_irq_1 ; 
 int qmgr_irq_2 ; 
 int /*<<< orphan*/  qmgr_lock ; 
 TYPE_1__* qmgr_regs ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int* used_sram_bitmap ; 

__attribute__((used)) static int ixp4xx_qmgr_probe(struct platform_device *pdev)
{
	int i, err;
	irq_handler_t handler1, handler2;
	struct device *dev = &pdev->dev;
	struct resource *res;
	int irq1, irq2;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;
	qmgr_regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(qmgr_regs))
		return PTR_ERR(qmgr_regs);

	irq1 = platform_get_irq(pdev, 0);
	if (irq1 <= 0)
		return irq1 ? irq1 : -EINVAL;
	qmgr_irq_1 = irq1;
	irq2 = platform_get_irq(pdev, 1);
	if (irq2 <= 0)
		return irq2 ? irq2 : -EINVAL;
	qmgr_irq_2 = irq2;

	/* reset qmgr registers */
	for (i = 0; i < 4; i++) {
		__raw_writel(0x33333333, &qmgr_regs->stat1[i]);
		__raw_writel(0, &qmgr_regs->irqsrc[i]);
	}
	for (i = 0; i < 2; i++) {
		__raw_writel(0, &qmgr_regs->stat2[i]);
		__raw_writel(0xFFFFFFFF, &qmgr_regs->irqstat[i]); /* clear */
		__raw_writel(0, &qmgr_regs->irqen[i]);
	}

	__raw_writel(0xFFFFFFFF, &qmgr_regs->statne_h);
	__raw_writel(0, &qmgr_regs->statf_h);

	for (i = 0; i < QUEUES; i++)
		__raw_writel(0, &qmgr_regs->sram[i]);

	if (cpu_is_ixp42x_rev_a0()) {
		handler1 = qmgr_irq1_a0;
		handler2 = qmgr_irq2_a0;
	} else
		handler1 = handler2 = qmgr_irq;

	err = devm_request_irq(dev, irq1, handler1, 0, "IXP4xx Queue Manager",
			       NULL);
	if (err) {
		dev_err(dev, "failed to request IRQ%i (%i)\n",
			irq1, err);
		return err;
	}

	err = devm_request_irq(dev, irq2, handler2, 0, "IXP4xx Queue Manager",
			       NULL);
	if (err) {
		dev_err(dev, "failed to request IRQ%i (%i)\n",
			irq2, err);
		return err;
	}

	used_sram_bitmap[0] = 0xF; /* 4 first pages reserved for config */
	spin_lock_init(&qmgr_lock);

	dev_info(dev, "IXP4xx Queue Manager initialized.\n");
	return 0;
}