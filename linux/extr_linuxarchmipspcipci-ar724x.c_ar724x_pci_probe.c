#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct platform_device {int id; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_2__* mem_resource; TYPE_1__* io_resource; int /*<<< orphan*/ * pci_ops; } ;
struct TYPE_5__ {char* name; void* flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; struct resource* parent; } ;
struct TYPE_4__ {char* name; void* flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; struct resource* parent; } ;
struct ar724x_pci_controller {scalar_t__ irq; TYPE_3__ pci_controller; int /*<<< orphan*/  link_up; TYPE_2__ mem_res; TYPE_1__ io_res; void* crp_base; void* devcfg_base; void* ctrl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR724X_PCI_CMD_INIT ; 
 int AR724X_RESET_PCIE ; 
 int /*<<< orphan*/  AR724X_RESET_REG_RESET_MODULE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* IORESOURCE_IO ; 
 void* IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  ar724x_pci_check_link (struct ar724x_pci_controller*) ; 
 int /*<<< orphan*/  ar724x_pci_hw_init (struct ar724x_pci_controller*) ; 
 int /*<<< orphan*/  ar724x_pci_irq_init (struct ar724x_pci_controller*,int) ; 
 int /*<<< orphan*/  ar724x_pci_local_write (struct ar724x_pci_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar724x_pci_ops ; 
 int ath79_reset_rr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct ar724x_pci_controller* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,void*,char*) ; 
 int /*<<< orphan*/  register_pci_controller (TYPE_3__*) ; 

__attribute__((used)) static int ar724x_pci_probe(struct platform_device *pdev)
{
	struct ar724x_pci_controller *apc;
	struct resource *res;
	int id;

	id = pdev->id;
	if (id == -1)
		id = 0;

	apc = devm_kzalloc(&pdev->dev, sizeof(struct ar724x_pci_controller),
			    GFP_KERNEL);
	if (!apc)
		return -ENOMEM;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "ctrl_base");
	apc->ctrl_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(apc->ctrl_base))
		return PTR_ERR(apc->ctrl_base);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "cfg_base");
	apc->devcfg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(apc->devcfg_base))
		return PTR_ERR(apc->devcfg_base);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "crp_base");
	apc->crp_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(apc->crp_base))
		return PTR_ERR(apc->crp_base);

	apc->irq = platform_get_irq(pdev, 0);
	if (apc->irq < 0)
		return -EINVAL;

	res = platform_get_resource_byname(pdev, IORESOURCE_IO, "io_base");
	if (!res)
		return -EINVAL;

	apc->io_res.parent = res;
	apc->io_res.name = "PCI IO space";
	apc->io_res.start = res->start;
	apc->io_res.end = res->end;
	apc->io_res.flags = IORESOURCE_IO;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mem_base");
	if (!res)
		return -EINVAL;

	apc->mem_res.parent = res;
	apc->mem_res.name = "PCI memory space";
	apc->mem_res.start = res->start;
	apc->mem_res.end = res->end;
	apc->mem_res.flags = IORESOURCE_MEM;

	apc->pci_controller.pci_ops = &ar724x_pci_ops;
	apc->pci_controller.io_resource = &apc->io_res;
	apc->pci_controller.mem_resource = &apc->mem_res;

	/*
	 * Do the full PCIE Root Complex Initialization Sequence if the PCIe
	 * host controller is in reset.
	 */
	if (ath79_reset_rr(AR724X_RESET_REG_RESET_MODULE) & AR724X_RESET_PCIE)
		ar724x_pci_hw_init(apc);

	apc->link_up = ar724x_pci_check_link(apc);
	if (!apc->link_up)
		dev_warn(&pdev->dev, "PCIe link is down\n");

	ar724x_pci_irq_init(apc, id);

	ar724x_pci_local_write(apc, PCI_COMMAND, 4, AR724X_PCI_CMD_INIT);

	register_pci_controller(&apc->pci_controller);

	return 0;
}