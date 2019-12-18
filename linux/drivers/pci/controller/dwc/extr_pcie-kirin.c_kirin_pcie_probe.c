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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct kirin_pcie {scalar_t__ gpio_id_reset; struct dw_pcie* pci; } ;
struct dw_pcie {int /*<<< orphan*/ * ops; struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int kirin_add_pcie_port (struct dw_pcie*,struct platform_device*) ; 
 int /*<<< orphan*/  kirin_dw_pcie_ops ; 
 int kirin_pcie_get_clk (struct kirin_pcie*,struct platform_device*) ; 
 int kirin_pcie_get_resource (struct kirin_pcie*,struct platform_device*) ; 
 int kirin_pcie_power_on (struct kirin_pcie*) ; 
 scalar_t__ of_get_named_gpio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct kirin_pcie*) ; 

__attribute__((used)) static int kirin_pcie_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct kirin_pcie *kirin_pcie;
	struct dw_pcie *pci;
	int ret;

	if (!dev->of_node) {
		dev_err(dev, "NULL node\n");
		return -EINVAL;
	}

	kirin_pcie = devm_kzalloc(dev, sizeof(struct kirin_pcie), GFP_KERNEL);
	if (!kirin_pcie)
		return -ENOMEM;

	pci = devm_kzalloc(dev, sizeof(*pci), GFP_KERNEL);
	if (!pci)
		return -ENOMEM;

	pci->dev = dev;
	pci->ops = &kirin_dw_pcie_ops;
	kirin_pcie->pci = pci;

	ret = kirin_pcie_get_clk(kirin_pcie, pdev);
	if (ret)
		return ret;

	ret = kirin_pcie_get_resource(kirin_pcie, pdev);
	if (ret)
		return ret;

	kirin_pcie->gpio_id_reset = of_get_named_gpio(dev->of_node,
						      "reset-gpios", 0);
	if (kirin_pcie->gpio_id_reset < 0)
		return -ENODEV;

	ret = kirin_pcie_power_on(kirin_pcie);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, kirin_pcie);

	return kirin_add_pcie_port(pci, pdev);
}