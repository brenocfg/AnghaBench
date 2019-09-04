#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_3__ {int /*<<< orphan*/  platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct dw_mci_drv_data {int dummy; } ;
struct dw_mci {scalar_t__ irq; int /*<<< orphan*/  phy_regs; int /*<<< orphan*/  regs; int /*<<< orphan*/  pdata; scalar_t__ irq_flags; TYPE_1__* dev; struct dw_mci_drv_data const* drv_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct dw_mci* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int dw_mci_probe (struct dw_mci*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dw_mci*) ; 

int dw_mci_pltfm_register(struct platform_device *pdev,
			  const struct dw_mci_drv_data *drv_data)
{
	struct dw_mci *host;
	struct resource	*regs;

	host = devm_kzalloc(&pdev->dev, sizeof(struct dw_mci), GFP_KERNEL);
	if (!host)
		return -ENOMEM;

	host->irq = platform_get_irq(pdev, 0);
	if (host->irq < 0)
		return host->irq;

	host->drv_data = drv_data;
	host->dev = &pdev->dev;
	host->irq_flags = 0;
	host->pdata = pdev->dev.platform_data;

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->regs = devm_ioremap_resource(&pdev->dev, regs);
	if (IS_ERR(host->regs))
		return PTR_ERR(host->regs);

	/* Get registers' physical base address */
	host->phy_regs = regs->start;

	platform_set_drvdata(pdev, host);
	return dw_mci_probe(host);
}