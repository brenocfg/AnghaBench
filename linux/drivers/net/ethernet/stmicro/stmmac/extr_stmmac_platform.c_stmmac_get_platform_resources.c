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
struct stmmac_resources {int irq; int wol_irq; int lpi_irq; int /*<<< orphan*/  addr; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  memset (struct stmmac_resources*,int /*<<< orphan*/ ,int) ; 
 void* platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int stmmac_get_platform_resources(struct platform_device *pdev,
				  struct stmmac_resources *stmmac_res)
{
	struct resource *res;

	memset(stmmac_res, 0, sizeof(*stmmac_res));

	/* Get IRQ information early to have an ability to ask for deferred
	 * probe if needed before we went too far with resource allocation.
	 */
	stmmac_res->irq = platform_get_irq_byname(pdev, "macirq");
	if (stmmac_res->irq < 0)
		return stmmac_res->irq;

	/* On some platforms e.g. SPEAr the wake up irq differs from the mac irq
	 * The external wake up irq can be passed through the platform code
	 * named as "eth_wake_irq"
	 *
	 * In case the wake up interrupt is not passed from the platform
	 * so the driver will continue to use the mac irq (ndev->irq)
	 */
	stmmac_res->wol_irq = platform_get_irq_byname(pdev, "eth_wake_irq");
	if (stmmac_res->wol_irq < 0) {
		if (stmmac_res->wol_irq == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		stmmac_res->wol_irq = stmmac_res->irq;
	}

	stmmac_res->lpi_irq = platform_get_irq_byname(pdev, "eth_lpi");
	if (stmmac_res->lpi_irq == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	stmmac_res->addr = devm_ioremap_resource(&pdev->dev, res);

	return PTR_ERR_OR_ZERO(stmmac_res->addr);
}