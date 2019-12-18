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
struct resource {int dummy; } ;
struct qcom_pcie {void* phy; TYPE_1__* ops; void* elbi; void* parf; void* reset; struct dw_pcie* pci; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct pcie_port {int msi_irq; int /*<<< orphan*/ * ops; } ;
struct dw_pcie {void* dbi_base; struct pcie_port pp; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct TYPE_2__ {int (* get_resources ) (struct qcom_pcie*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_pci_remap_cfg_resource (struct device*,struct resource*) ; 
 void* devm_phy_optional_get (struct device*,char*) ; 
 int dw_pcie_host_init (struct pcie_port*) ; 
 int /*<<< orphan*/  dw_pcie_ops ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 int phy_init (void*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qcom_pcie*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  qcom_pcie_dw_ops ; 
 int stub1 (struct qcom_pcie*) ; 

__attribute__((used)) static int qcom_pcie_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct pcie_port *pp;
	struct dw_pcie *pci;
	struct qcom_pcie *pcie;
	int ret;

	pcie = devm_kzalloc(dev, sizeof(*pcie), GFP_KERNEL);
	if (!pcie)
		return -ENOMEM;

	pci = devm_kzalloc(dev, sizeof(*pci), GFP_KERNEL);
	if (!pci)
		return -ENOMEM;

	pm_runtime_enable(dev);
	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		pm_runtime_disable(dev);
		return ret;
	}

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;
	pp = &pci->pp;

	pcie->pci = pci;

	pcie->ops = of_device_get_match_data(dev);

	pcie->reset = devm_gpiod_get_optional(dev, "perst", GPIOD_OUT_HIGH);
	if (IS_ERR(pcie->reset)) {
		ret = PTR_ERR(pcie->reset);
		goto err_pm_runtime_put;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "parf");
	pcie->parf = devm_ioremap_resource(dev, res);
	if (IS_ERR(pcie->parf)) {
		ret = PTR_ERR(pcie->parf);
		goto err_pm_runtime_put;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	pci->dbi_base = devm_pci_remap_cfg_resource(dev, res);
	if (IS_ERR(pci->dbi_base)) {
		ret = PTR_ERR(pci->dbi_base);
		goto err_pm_runtime_put;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "elbi");
	pcie->elbi = devm_ioremap_resource(dev, res);
	if (IS_ERR(pcie->elbi)) {
		ret = PTR_ERR(pcie->elbi);
		goto err_pm_runtime_put;
	}

	pcie->phy = devm_phy_optional_get(dev, "pciephy");
	if (IS_ERR(pcie->phy)) {
		ret = PTR_ERR(pcie->phy);
		goto err_pm_runtime_put;
	}

	ret = pcie->ops->get_resources(pcie);
	if (ret)
		goto err_pm_runtime_put;

	pp->ops = &qcom_pcie_dw_ops;

	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		pp->msi_irq = platform_get_irq_byname(pdev, "msi");
		if (pp->msi_irq < 0) {
			ret = pp->msi_irq;
			goto err_pm_runtime_put;
		}
	}

	ret = phy_init(pcie->phy);
	if (ret) {
		pm_runtime_disable(&pdev->dev);
		goto err_pm_runtime_put;
	}

	platform_set_drvdata(pdev, pcie);

	ret = dw_pcie_host_init(pp);
	if (ret) {
		dev_err(dev, "cannot initialize host\n");
		pm_runtime_disable(&pdev->dev);
		goto err_pm_runtime_put;
	}

	return 0;

err_pm_runtime_put:
	pm_runtime_put(dev);
	pm_runtime_disable(dev);

	return ret;
}