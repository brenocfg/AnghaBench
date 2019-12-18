#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int num_res; int size_data; struct platform_device* pclk; struct platform_device* hclk; int /*<<< orphan*/  dma_mask; struct resource* data; struct resource* res; int /*<<< orphan*/  id; void* name; int /*<<< orphan*/  fwnode; TYPE_1__* parent; int /*<<< orphan*/  start; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; } ;
struct platform_device_info {int num_res; int size_data; struct platform_device* pclk; struct platform_device* hclk; int /*<<< orphan*/  dma_mask; struct platform_device_info* data; struct platform_device_info* res; int /*<<< orphan*/  id; void* name; int /*<<< orphan*/  fwnode; TYPE_1__* parent; int /*<<< orphan*/  start; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; } ;
struct platform_device {int dummy; } ;
struct pci_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;
struct pci_dev {int /*<<< orphan*/  dma_mask; int /*<<< orphan*/  devfn; TYPE_1__ dev; } ;
struct macb_platform_data {int num_res; int size_data; struct platform_device* pclk; struct platform_device* hclk; int /*<<< orphan*/  dma_mask; struct macb_platform_data* data; struct macb_platform_data* res; int /*<<< orphan*/  id; void* name; int /*<<< orphan*/  fwnode; TYPE_1__* parent; int /*<<< orphan*/  start; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; } ;
typedef  int /*<<< orphan*/  plat_info ;
typedef  int /*<<< orphan*/  plat_data ;

/* Variables and functions */
 int ARRAY_SIZE (struct resource*) ; 
 int /*<<< orphan*/  GEM_HCLK_RATE ; 
 int /*<<< orphan*/  GEM_PCLK_RATE ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 void* PCI_DRIVER_NAME ; 
 void* PLAT_DRIVER_NAME ; 
 int PTR_ERR (struct platform_device*) ; 
 void* clk_register_fixed_rate (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct resource*,int,int) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_end (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct platform_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 struct platform_device* platform_device_register_full (struct resource*) ; 

__attribute__((used)) static int macb_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int err;
	struct platform_device *plat_dev;
	struct platform_device_info plat_info;
	struct macb_platform_data plat_data;
	struct resource res[2];

	/* enable pci device */
	err = pcim_enable_device(pdev);
	if (err < 0) {
		dev_err(&pdev->dev, "Enabling PCI device has failed: %d", err);
		return err;
	}

	pci_set_master(pdev);

	/* set up resources */
	memset(res, 0x00, sizeof(struct resource) * ARRAY_SIZE(res));
	res[0].start = pci_resource_start(pdev, 0);
	res[0].end = pci_resource_end(pdev, 0);
	res[0].name = PCI_DRIVER_NAME;
	res[0].flags = IORESOURCE_MEM;
	res[1].start = pci_irq_vector(pdev, 0);
	res[1].name = PCI_DRIVER_NAME;
	res[1].flags = IORESOURCE_IRQ;

	dev_info(&pdev->dev, "EMAC physical base addr: %pa\n",
		 &res[0].start);

	/* set up macb platform data */
	memset(&plat_data, 0, sizeof(plat_data));

	/* initialize clocks */
	plat_data.pclk = clk_register_fixed_rate(&pdev->dev, "pclk", NULL, 0,
						 GEM_PCLK_RATE);
	if (IS_ERR(plat_data.pclk)) {
		err = PTR_ERR(plat_data.pclk);
		goto err_pclk_register;
	}

	plat_data.hclk = clk_register_fixed_rate(&pdev->dev, "hclk", NULL, 0,
						 GEM_HCLK_RATE);
	if (IS_ERR(plat_data.hclk)) {
		err = PTR_ERR(plat_data.hclk);
		goto err_hclk_register;
	}

	/* set up platform device info */
	memset(&plat_info, 0, sizeof(plat_info));
	plat_info.parent = &pdev->dev;
	plat_info.fwnode = pdev->dev.fwnode;
	plat_info.name = PLAT_DRIVER_NAME;
	plat_info.id = pdev->devfn;
	plat_info.res = res;
	plat_info.num_res = ARRAY_SIZE(res);
	plat_info.data = &plat_data;
	plat_info.size_data = sizeof(plat_data);
	plat_info.dma_mask = pdev->dma_mask;

	/* register platform device */
	plat_dev = platform_device_register_full(&plat_info);
	if (IS_ERR(plat_dev)) {
		err = PTR_ERR(plat_dev);
		goto err_plat_dev_register;
	}

	pci_set_drvdata(pdev, plat_dev);

	return 0;

err_plat_dev_register:
	clk_unregister(plat_data.hclk);

err_hclk_register:
	clk_unregister(plat_data.pclk);

err_pclk_register:
	return err;
}