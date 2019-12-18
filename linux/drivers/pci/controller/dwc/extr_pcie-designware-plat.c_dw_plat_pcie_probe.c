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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct dw_plat_pcie_of_data {scalar_t__ mode; } ;
struct dw_plat_pcie {int mode; struct dw_pcie* pci; } ;
struct dw_pcie {int /*<<< orphan*/  dbi_base; int /*<<< orphan*/ * ops; struct device* dev; } ;
typedef  enum dw_pcie_device_mode { ____Placeholder_dw_pcie_device_mode } dw_pcie_device_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCIE_DW_PLAT_EP ; 
 int /*<<< orphan*/  CONFIG_PCIE_DW_PLAT_HOST ; 
#define  DW_PCIE_EP_TYPE 129 
#define  DW_PCIE_RC_TYPE 128 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_ops ; 
 int dw_plat_add_pcie_ep (struct dw_plat_pcie*,struct platform_device*) ; 
 int dw_plat_add_pcie_port (struct dw_plat_pcie*,struct platform_device*) ; 
 int /*<<< orphan*/  dw_plat_pcie_of_match ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dw_plat_pcie*) ; 

__attribute__((used)) static int dw_plat_pcie_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct dw_plat_pcie *dw_plat_pcie;
	struct dw_pcie *pci;
	struct resource *res;  /* Resource from DT */
	int ret;
	const struct of_device_id *match;
	const struct dw_plat_pcie_of_data *data;
	enum dw_pcie_device_mode mode;

	match = of_match_device(dw_plat_pcie_of_match, dev);
	if (!match)
		return -EINVAL;

	data = (struct dw_plat_pcie_of_data *)match->data;
	mode = (enum dw_pcie_device_mode)data->mode;

	dw_plat_pcie = devm_kzalloc(dev, sizeof(*dw_plat_pcie), GFP_KERNEL);
	if (!dw_plat_pcie)
		return -ENOMEM;

	pci = devm_kzalloc(dev, sizeof(*pci), GFP_KERNEL);
	if (!pci)
		return -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	dw_plat_pcie->pci = pci;
	dw_plat_pcie->mode = mode;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	if (!res)
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	pci->dbi_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(pci->dbi_base))
		return PTR_ERR(pci->dbi_base);

	platform_set_drvdata(pdev, dw_plat_pcie);

	switch (dw_plat_pcie->mode) {
	case DW_PCIE_RC_TYPE:
		if (!IS_ENABLED(CONFIG_PCIE_DW_PLAT_HOST))
			return -ENODEV;

		ret = dw_plat_add_pcie_port(dw_plat_pcie, pdev);
		if (ret < 0)
			return ret;
		break;
	case DW_PCIE_EP_TYPE:
		if (!IS_ENABLED(CONFIG_PCIE_DW_PLAT_EP))
			return -ENODEV;

		ret = dw_plat_add_pcie_ep(dw_plat_pcie, pdev);
		if (ret < 0)
			return ret;
		break;
	default:
		dev_err(dev, "INVALID device type %d\n", dw_plat_pcie->mode);
	}

	return 0;
}