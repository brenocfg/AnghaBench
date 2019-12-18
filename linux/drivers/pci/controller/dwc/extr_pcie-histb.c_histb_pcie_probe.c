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
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct pcie_port {scalar_t__ msi_irq; int /*<<< orphan*/ * ops; } ;
struct histb_pcie {int /*<<< orphan*/ * phy; int /*<<< orphan*/ * bus_reset; int /*<<< orphan*/ * sys_reset; int /*<<< orphan*/ * soft_reset; int /*<<< orphan*/ * bus_clk; int /*<<< orphan*/ * sys_clk; int /*<<< orphan*/ * pipe_clk; int /*<<< orphan*/ * aux_clk; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/ * vpcie; int /*<<< orphan*/ * ctrl; struct dw_pcie* pci; } ;
struct dw_pcie {int /*<<< orphan*/ * dbi_base; int /*<<< orphan*/ * ops; struct device* dev; struct pcie_port pp; } ;
struct device_node {int dummy; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long GPIOF_ACTIVE_LOW ; 
 unsigned long GPIOF_DIR_OUT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,unsigned long,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_phy_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (struct device*,char*) ; 
 void* devm_reset_control_get (struct device*,char*) ; 
 int dw_pcie_host_init (struct pcie_port*) ; 
 int /*<<< orphan*/  dw_pcie_ops ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int histb_pcie_host_enable (struct pcie_port*) ; 
 int /*<<< orphan*/  histb_pcie_host_ops ; 
 int /*<<< orphan*/  of_get_named_gpio_flags (struct device_node*,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  phy_init (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct histb_pcie*) ; 

__attribute__((used)) static int histb_pcie_probe(struct platform_device *pdev)
{
	struct histb_pcie *hipcie;
	struct dw_pcie *pci;
	struct pcie_port *pp;
	struct resource *res;
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	enum of_gpio_flags of_flags;
	unsigned long flag = GPIOF_DIR_OUT;
	int ret;

	hipcie = devm_kzalloc(dev, sizeof(*hipcie), GFP_KERNEL);
	if (!hipcie)
		return -ENOMEM;

	pci = devm_kzalloc(dev, sizeof(*pci), GFP_KERNEL);
	if (!pci)
		return -ENOMEM;

	hipcie->pci = pci;
	pp = &pci->pp;
	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "control");
	hipcie->ctrl = devm_ioremap_resource(dev, res);
	if (IS_ERR(hipcie->ctrl)) {
		dev_err(dev, "cannot get control reg base\n");
		return PTR_ERR(hipcie->ctrl);
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "rc-dbi");
	pci->dbi_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(pci->dbi_base)) {
		dev_err(dev, "cannot get rc-dbi base\n");
		return PTR_ERR(pci->dbi_base);
	}

	hipcie->vpcie = devm_regulator_get_optional(dev, "vpcie");
	if (IS_ERR(hipcie->vpcie)) {
		if (PTR_ERR(hipcie->vpcie) != -ENODEV)
			return PTR_ERR(hipcie->vpcie);
		hipcie->vpcie = NULL;
	}

	hipcie->reset_gpio = of_get_named_gpio_flags(np,
				"reset-gpios", 0, &of_flags);
	if (of_flags & OF_GPIO_ACTIVE_LOW)
		flag |= GPIOF_ACTIVE_LOW;
	if (gpio_is_valid(hipcie->reset_gpio)) {
		ret = devm_gpio_request_one(dev, hipcie->reset_gpio,
				flag, "PCIe device power control");
		if (ret) {
			dev_err(dev, "unable to request gpio\n");
			return ret;
		}
	}

	hipcie->aux_clk = devm_clk_get(dev, "aux");
	if (IS_ERR(hipcie->aux_clk)) {
		dev_err(dev, "Failed to get PCIe aux clk\n");
		return PTR_ERR(hipcie->aux_clk);
	}

	hipcie->pipe_clk = devm_clk_get(dev, "pipe");
	if (IS_ERR(hipcie->pipe_clk)) {
		dev_err(dev, "Failed to get PCIe pipe clk\n");
		return PTR_ERR(hipcie->pipe_clk);
	}

	hipcie->sys_clk = devm_clk_get(dev, "sys");
	if (IS_ERR(hipcie->sys_clk)) {
		dev_err(dev, "Failed to get PCIEe sys clk\n");
		return PTR_ERR(hipcie->sys_clk);
	}

	hipcie->bus_clk = devm_clk_get(dev, "bus");
	if (IS_ERR(hipcie->bus_clk)) {
		dev_err(dev, "Failed to get PCIe bus clk\n");
		return PTR_ERR(hipcie->bus_clk);
	}

	hipcie->soft_reset = devm_reset_control_get(dev, "soft");
	if (IS_ERR(hipcie->soft_reset)) {
		dev_err(dev, "couldn't get soft reset\n");
		return PTR_ERR(hipcie->soft_reset);
	}

	hipcie->sys_reset = devm_reset_control_get(dev, "sys");
	if (IS_ERR(hipcie->sys_reset)) {
		dev_err(dev, "couldn't get sys reset\n");
		return PTR_ERR(hipcie->sys_reset);
	}

	hipcie->bus_reset = devm_reset_control_get(dev, "bus");
	if (IS_ERR(hipcie->bus_reset)) {
		dev_err(dev, "couldn't get bus reset\n");
		return PTR_ERR(hipcie->bus_reset);
	}

	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		pp->msi_irq = platform_get_irq_byname(pdev, "msi");
		if (pp->msi_irq < 0) {
			dev_err(dev, "Failed to get MSI IRQ\n");
			return pp->msi_irq;
		}
	}

	hipcie->phy = devm_phy_get(dev, "phy");
	if (IS_ERR(hipcie->phy)) {
		dev_info(dev, "no pcie-phy found\n");
		hipcie->phy = NULL;
		/* fall through here!
		 * if no pcie-phy found, phy init
		 * should be done under boot!
		 */
	} else {
		phy_init(hipcie->phy);
	}

	pp->ops = &histb_pcie_host_ops;

	platform_set_drvdata(pdev, hipcie);

	ret = histb_pcie_host_enable(pp);
	if (ret) {
		dev_err(dev, "failed to enable host\n");
		return ret;
	}

	ret = dw_pcie_host_init(pp);
	if (ret) {
		dev_err(dev, "failed to initialize host\n");
		return ret;
	}

	return 0;
}