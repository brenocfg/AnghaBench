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
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; struct device dev; } ;
struct mfd_cell {int pdata_size; struct dwapb_platform_data* platform_data; scalar_t__ resources; } ;
struct dwapb_platform_data {TYPE_1__* properties; int /*<<< orphan*/  nports; } ;
struct TYPE_2__ {int has_irq; int irq_shared; int /*<<< orphan*/ * irq; int /*<<< orphan*/  gpio_base; int /*<<< orphan*/  ngpio; scalar_t__ idx; int /*<<< orphan*/ * fwnode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTEL_QUARK_GPIO_NPORTS ; 
 size_t INTEL_QUARK_IORES_MEM ; 
 int /*<<< orphan*/  INTEL_QUARK_MFD_GPIO_BASE ; 
 int /*<<< orphan*/  INTEL_QUARK_MFD_NGPIO ; 
 int /*<<< orphan*/  MFD_GPIO_BAR ; 
 TYPE_1__* devm_kcalloc (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct dwapb_platform_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_end (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_quark_gpio_setup(struct pci_dev *pdev, struct mfd_cell *cell)
{
	struct dwapb_platform_data *pdata;
	struct resource *res = (struct resource *)cell->resources;
	struct device *dev = &pdev->dev;

	res[INTEL_QUARK_IORES_MEM].start =
		pci_resource_start(pdev, MFD_GPIO_BAR);
	res[INTEL_QUARK_IORES_MEM].end =
		pci_resource_end(pdev, MFD_GPIO_BAR);

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	/* For intel quark x1000, it has only one port: portA */
	pdata->nports = INTEL_QUARK_GPIO_NPORTS;
	pdata->properties = devm_kcalloc(dev, pdata->nports,
					 sizeof(*pdata->properties),
					 GFP_KERNEL);
	if (!pdata->properties)
		return -ENOMEM;

	/* Set the properties for portA */
	pdata->properties->fwnode	= NULL;
	pdata->properties->idx		= 0;
	pdata->properties->ngpio	= INTEL_QUARK_MFD_NGPIO;
	pdata->properties->gpio_base	= INTEL_QUARK_MFD_GPIO_BASE;
	pdata->properties->irq[0]	= pdev->irq;
	pdata->properties->has_irq	= true;
	pdata->properties->irq_shared	= true;

	cell->platform_data = pdata;
	cell->pdata_size = sizeof(*pdata);

	return 0;
}