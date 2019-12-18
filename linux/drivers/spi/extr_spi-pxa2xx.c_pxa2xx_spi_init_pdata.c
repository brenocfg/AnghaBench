#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ssp_device {int type; int /*<<< orphan*/  port_id; struct platform_device* pdev; int /*<<< orphan*/  irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  phys_base; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct pxa2xx_spi_controller {int num_chipselect; int enable_dma; int dma_burst_size; int /*<<< orphan*/  is_slave; int /*<<< orphan*/  dma_filter; int /*<<< orphan*/  rx_param; int /*<<< orphan*/  tx_param; struct ssp_device ssp; } ;
struct TYPE_9__ {scalar_t__ of_node; int /*<<< orphan*/  parent; TYPE_1__* driver; } ;
struct platform_device {TYPE_2__ dev; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct of_device_id {scalar_t__ data; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct acpi_device {int dummy; } ;
typedef  enum pxa_ssp_type { ____Placeholder_pxa_ssp_type } pxa_ssp_type ;
struct TYPE_8__ {int /*<<< orphan*/  acpi_match_table; int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (TYPE_2__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ dev_is_pci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct pxa2xx_spi_controller* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_property_read_bool (scalar_t__,char*) ; 
 struct pci_device_id* pci_match_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_spi_get_port_id (struct acpi_device*) ; 
 int /*<<< orphan*/  pxa2xx_spi_idma_filter ; 
 int /*<<< orphan*/  pxa2xx_spi_pci_compound_match ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pxa2xx_spi_controller *
pxa2xx_spi_init_pdata(struct platform_device *pdev)
{
	struct pxa2xx_spi_controller *pdata;
	struct acpi_device *adev;
	struct ssp_device *ssp;
	struct resource *res;
	const struct acpi_device_id *adev_id = NULL;
	const struct pci_device_id *pcidev_id = NULL;
	const struct of_device_id *of_id = NULL;
	enum pxa_ssp_type type;

	adev = ACPI_COMPANION(&pdev->dev);

	if (pdev->dev.of_node)
		of_id = of_match_device(pdev->dev.driver->of_match_table,
					&pdev->dev);
	else if (dev_is_pci(pdev->dev.parent))
		pcidev_id = pci_match_id(pxa2xx_spi_pci_compound_match,
					 to_pci_dev(pdev->dev.parent));
	else if (adev)
		adev_id = acpi_match_device(pdev->dev.driver->acpi_match_table,
					    &pdev->dev);
	else
		return NULL;

	if (adev_id)
		type = (enum pxa_ssp_type)adev_id->driver_data;
	else if (pcidev_id)
		type = (enum pxa_ssp_type)pcidev_id->driver_data;
	else if (of_id)
		type = (enum pxa_ssp_type)of_id->data;
	else
		return NULL;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return NULL;

	ssp = &pdata->ssp;

	ssp->phys_base = res->start;
	ssp->mmio_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ssp->mmio_base))
		return NULL;

#ifdef CONFIG_PCI
	if (pcidev_id) {
		pdata->tx_param = pdev->dev.parent;
		pdata->rx_param = pdev->dev.parent;
		pdata->dma_filter = pxa2xx_spi_idma_filter;
	}
#endif

	ssp->clk = devm_clk_get(&pdev->dev, NULL);
	ssp->irq = platform_get_irq(pdev, 0);
	ssp->type = type;
	ssp->pdev = pdev;
	ssp->port_id = pxa2xx_spi_get_port_id(adev);

	pdata->is_slave = of_property_read_bool(pdev->dev.of_node, "spi-slave");
	pdata->num_chipselect = 1;
	pdata->enable_dma = true;
	pdata->dma_burst_size = 1;

	return pdata;
}