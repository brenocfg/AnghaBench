#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct priv {TYPE_1__* bus; int /*<<< orphan*/  base; int /*<<< orphan*/  mapbase; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  get_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAM_HEADER_SIZE ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long IORESOURCE_IO ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int PTR_ERR (TYPE_1__*) ; 
 int chameleon_parse_cells (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct resource* devm_request_mem_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mcb_alloc_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcb_bus_add_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  mcb_pci_get_irq ; 
 int /*<<< orphan*/  mcb_release_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 unsigned long pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct priv*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static int mcb_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct resource *res;
	struct priv *priv;
	int ret;
	unsigned long flags;

	priv = devm_kzalloc(&pdev->dev, sizeof(struct priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ret = pci_enable_device(pdev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to enable PCI device\n");
		return -ENODEV;
	}
	pci_set_master(pdev);

	priv->mapbase = pci_resource_start(pdev, 0);
	if (!priv->mapbase) {
		dev_err(&pdev->dev, "No PCI resource\n");
		ret = -ENODEV;
		goto out_disable;
	}

	res = devm_request_mem_region(&pdev->dev, priv->mapbase,
				      CHAM_HEADER_SIZE,
				      KBUILD_MODNAME);
	if (!res) {
		dev_err(&pdev->dev, "Failed to request PCI memory\n");
		ret = -EBUSY;
		goto out_disable;
	}

	priv->base = devm_ioremap(&pdev->dev, priv->mapbase, CHAM_HEADER_SIZE);
	if (!priv->base) {
		dev_err(&pdev->dev, "Cannot ioremap\n");
		ret = -ENOMEM;
		goto out_disable;
	}

	flags = pci_resource_flags(pdev, 0);
	if (flags & IORESOURCE_IO) {
		ret = -ENOTSUPP;
		dev_err(&pdev->dev,
			"IO mapped PCI devices are not supported\n");
		goto out_disable;
	}

	pci_set_drvdata(pdev, priv);

	priv->bus = mcb_alloc_bus(&pdev->dev);
	if (IS_ERR(priv->bus)) {
		ret = PTR_ERR(priv->bus);
		goto out_disable;
	}

	priv->bus->get_irq = mcb_pci_get_irq;

	ret = chameleon_parse_cells(priv->bus, priv->mapbase, priv->base);
	if (ret < 0)
		goto out_mcb_bus;

	dev_dbg(&pdev->dev, "Found %d cells\n", ret);

	mcb_bus_add_devices(priv->bus);

	return 0;

out_mcb_bus:
	mcb_release_bus(priv->bus);
out_disable:
	pci_disable_device(pdev);
	return ret;
}