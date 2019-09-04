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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mtk_ddp {int /*<<< orphan*/  mutex_mod; int /*<<< orphan*/  regs; int /*<<< orphan*/  clk; TYPE_1__* mutex; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct mtk_ddp* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_ddp*) ; 

__attribute__((used)) static int mtk_ddp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mtk_ddp *ddp;
	struct resource *regs;
	int i;

	ddp = devm_kzalloc(dev, sizeof(*ddp), GFP_KERNEL);
	if (!ddp)
		return -ENOMEM;

	for (i = 0; i < 10; i++)
		ddp->mutex[i].id = i;

	ddp->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(ddp->clk)) {
		dev_err(dev, "Failed to get clock\n");
		return PTR_ERR(ddp->clk);
	}

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ddp->regs = devm_ioremap_resource(dev, regs);
	if (IS_ERR(ddp->regs)) {
		dev_err(dev, "Failed to map mutex registers\n");
		return PTR_ERR(ddp->regs);
	}

	ddp->mutex_mod = of_device_get_match_data(dev);

	platform_set_drvdata(pdev, ddp);

	return 0;
}