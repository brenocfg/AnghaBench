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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cqhci_host {int /*<<< orphan*/  mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cqhci_host* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cqhci_host* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

struct cqhci_host *cqhci_pltfm_init(struct platform_device *pdev)
{
	struct cqhci_host *cq_host;
	struct resource *cqhci_memres = NULL;

	/* check and setup CMDQ interface */
	cqhci_memres = platform_get_resource_byname(pdev, IORESOURCE_MEM,
						   "cqhci_mem");
	if (!cqhci_memres) {
		dev_dbg(&pdev->dev, "CMDQ not supported\n");
		return ERR_PTR(-EINVAL);
	}

	cq_host = devm_kzalloc(&pdev->dev, sizeof(*cq_host), GFP_KERNEL);
	if (!cq_host)
		return ERR_PTR(-ENOMEM);
	cq_host->mmio = devm_ioremap(&pdev->dev,
				     cqhci_memres->start,
				     resource_size(cqhci_memres));
	if (!cq_host->mmio) {
		dev_err(&pdev->dev, "failed to remap cqhci regs\n");
		return ERR_PTR(-EBUSY);
	}
	dev_dbg(&pdev->dev, "CMDQ ioremap: done\n");

	return cq_host;
}