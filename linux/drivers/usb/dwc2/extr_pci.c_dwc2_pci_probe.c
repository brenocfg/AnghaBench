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
struct resource {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
struct TYPE_2__ {struct device* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; struct device dev; } ;
struct dwc2_pci_glue {struct platform_device* dwc2; struct platform_device* phy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct resource*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct dwc2_pci_glue* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dwc2_pci_quirks (struct pci_dev*,struct platform_device*) ; 
 int /*<<< orphan*/  memset (struct resource*,int,int) ; 
 int /*<<< orphan*/  pci_resource_end (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct dwc2_pci_glue*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int) ; 
 struct platform_device* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 struct platform_device* usb_phy_generic_register () ; 
 int /*<<< orphan*/  usb_phy_generic_unregister (struct platform_device*) ; 

__attribute__((used)) static int dwc2_pci_probe(struct pci_dev *pci,
			  const struct pci_device_id *id)
{
	struct resource		res[2];
	struct platform_device	*dwc2;
	struct platform_device	*phy;
	int			ret;
	struct device		*dev = &pci->dev;
	struct dwc2_pci_glue	*glue;

	ret = pcim_enable_device(pci);
	if (ret) {
		dev_err(dev, "failed to enable pci device\n");
		return -ENODEV;
	}

	pci_set_master(pci);

	phy = usb_phy_generic_register();
	if (IS_ERR(phy)) {
		dev_err(dev, "error registering generic PHY (%ld)\n",
			PTR_ERR(phy));
		return PTR_ERR(phy);
	}

	dwc2 = platform_device_alloc("dwc2", PLATFORM_DEVID_AUTO);
	if (!dwc2) {
		dev_err(dev, "couldn't allocate dwc2 device\n");
		ret = -ENOMEM;
		goto err;
	}

	memset(res, 0x00, sizeof(struct resource) * ARRAY_SIZE(res));

	res[0].start	= pci_resource_start(pci, 0);
	res[0].end	= pci_resource_end(pci, 0);
	res[0].name	= "dwc2";
	res[0].flags	= IORESOURCE_MEM;

	res[1].start	= pci->irq;
	res[1].name	= "dwc2";
	res[1].flags	= IORESOURCE_IRQ;

	ret = platform_device_add_resources(dwc2, res, ARRAY_SIZE(res));
	if (ret) {
		dev_err(dev, "couldn't add resources to dwc2 device\n");
		goto err;
	}

	dwc2->dev.parent = dev;

	ret = dwc2_pci_quirks(pci, dwc2);
	if (ret)
		goto err;

	glue = devm_kzalloc(dev, sizeof(*glue), GFP_KERNEL);
	if (!glue) {
		ret = -ENOMEM;
		goto err;
	}

	ret = platform_device_add(dwc2);
	if (ret) {
		dev_err(dev, "failed to register dwc2 device\n");
		goto err;
	}

	glue->phy = phy;
	glue->dwc2 = dwc2;
	pci_set_drvdata(pci, glue);

	return 0;
err:
	usb_phy_generic_unregister(phy);
	platform_device_put(dwc2);
	return ret;
}