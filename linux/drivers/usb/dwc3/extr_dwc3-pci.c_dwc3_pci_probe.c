#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
struct property_entry {int dummy; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; struct device dev; } ;
struct dwc3_pci {TYPE_1__* dwc3; int /*<<< orphan*/  wakeup_work; struct pci_dev* pci; } ;
struct TYPE_8__ {struct device* parent; } ;
struct TYPE_7__ {TYPE_6__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  ACPI_COMPANION_SET (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int ARRAY_SIZE (struct resource*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 struct dwc3_pci* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dwc3_pci_quirks (struct dwc3_pci*) ; 
 int /*<<< orphan*/  dwc3_pci_resume_work ; 
 int /*<<< orphan*/  memset (struct resource*,int,int) ; 
 int /*<<< orphan*/  pci_resource_end (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct dwc3_pci*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int platform_device_add (TYPE_1__*) ; 
 int platform_device_add_properties (TYPE_1__*,struct property_entry*) ; 
 int platform_device_add_resources (TYPE_1__*,struct resource*,int) ; 
 TYPE_1__* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 

__attribute__((used)) static int dwc3_pci_probe(struct pci_dev *pci, const struct pci_device_id *id)
{
	struct property_entry *p = (struct property_entry *)id->driver_data;
	struct dwc3_pci		*dwc;
	struct resource		res[2];
	int			ret;
	struct device		*dev = &pci->dev;

	ret = pcim_enable_device(pci);
	if (ret) {
		dev_err(dev, "failed to enable pci device\n");
		return -ENODEV;
	}

	pci_set_master(pci);

	dwc = devm_kzalloc(dev, sizeof(*dwc), GFP_KERNEL);
	if (!dwc)
		return -ENOMEM;

	dwc->dwc3 = platform_device_alloc("dwc3", PLATFORM_DEVID_AUTO);
	if (!dwc->dwc3)
		return -ENOMEM;

	memset(res, 0x00, sizeof(struct resource) * ARRAY_SIZE(res));

	res[0].start	= pci_resource_start(pci, 0);
	res[0].end	= pci_resource_end(pci, 0);
	res[0].name	= "dwc_usb3";
	res[0].flags	= IORESOURCE_MEM;

	res[1].start	= pci->irq;
	res[1].name	= "dwc_usb3";
	res[1].flags	= IORESOURCE_IRQ;

	ret = platform_device_add_resources(dwc->dwc3, res, ARRAY_SIZE(res));
	if (ret) {
		dev_err(dev, "couldn't add resources to dwc3 device\n");
		goto err;
	}

	dwc->pci = pci;
	dwc->dwc3->dev.parent = dev;
	ACPI_COMPANION_SET(&dwc->dwc3->dev, ACPI_COMPANION(dev));

	ret = platform_device_add_properties(dwc->dwc3, p);
	if (ret < 0)
		goto err;

	ret = dwc3_pci_quirks(dwc);
	if (ret)
		goto err;

	ret = platform_device_add(dwc->dwc3);
	if (ret) {
		dev_err(dev, "failed to register dwc3 device\n");
		goto err;
	}

	device_init_wakeup(dev, true);
	pci_set_drvdata(pci, dwc);
	pm_runtime_put(dev);
#ifdef CONFIG_PM
	INIT_WORK(&dwc->wakeup_work, dwc3_pci_resume_work);
#endif

	return 0;
err:
	platform_device_put(dwc->dwc3);
	return ret;
}