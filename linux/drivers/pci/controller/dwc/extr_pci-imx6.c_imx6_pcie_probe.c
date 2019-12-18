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
typedef  int /*<<< orphan*/  u16 ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct imx6_pcie {int reset_gpio; int controller_id; int tx_deemph_gen1; int tx_deemph_gen2_3p5db; int tx_deemph_gen2_6db; int tx_swing_full; int tx_swing_low; int link_gen; int /*<<< orphan*/ * vpcie; int /*<<< orphan*/ * iomuxc_gpr; int /*<<< orphan*/ * turnoff_reset; int /*<<< orphan*/ * apps_reset; int /*<<< orphan*/ * pciephy_reset; int /*<<< orphan*/ * pcie_aux; int /*<<< orphan*/ * pcie_inbound_axi; TYPE_1__* drvdata; int /*<<< orphan*/ * pcie; int /*<<< orphan*/ * pcie_bus; int /*<<< orphan*/ * pcie_phy; scalar_t__ gpio_active_high; int /*<<< orphan*/ * phy_base; struct dw_pcie* pci; } ;
struct dw_pcie {int /*<<< orphan*/ * dbi_base; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int variant; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
#define  IMX6SX 130 
#define  IMX7D 129 
#define  IMX8MQ 128 
 int /*<<< orphan*/  IMX8MQ_PCIE2_BASE_ADDR ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ PCIE_RC_IMX6_MSI_CAP ; 
 scalar_t__ PCI_MSI_FLAGS ; 
 int /*<<< orphan*/  PCI_MSI_FLAGS_ENABLE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int devm_gpio_request_one (struct device*,int,int /*<<< orphan*/ ,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (struct device*,char*) ; 
 void* devm_reset_control_get_exclusive (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_reset_control_get_optional_exclusive (struct device*,char*) ; 
 int /*<<< orphan*/  dw_pcie_ops ; 
 int /*<<< orphan*/  dw_pcie_readw_dbi (struct dw_pcie*,scalar_t__) ; 
 int /*<<< orphan*/  dw_pcie_writew_dbi (struct dw_pcie*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int imx6_add_pcie_port (struct imx6_pcie*,struct platform_device*) ; 
 int imx6_pcie_attach_pd (struct device*) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 scalar_t__ pci_msi_enabled () ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx6_pcie*) ; 
 int /*<<< orphan*/ * syscon_regmap_lookup_by_compatible (char*) ; 

__attribute__((used)) static int imx6_pcie_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct dw_pcie *pci;
	struct imx6_pcie *imx6_pcie;
	struct device_node *np;
	struct resource *dbi_base;
	struct device_node *node = dev->of_node;
	int ret;
	u16 val;

	imx6_pcie = devm_kzalloc(dev, sizeof(*imx6_pcie), GFP_KERNEL);
	if (!imx6_pcie)
		return -ENOMEM;

	pci = devm_kzalloc(dev, sizeof(*pci), GFP_KERNEL);
	if (!pci)
		return -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	imx6_pcie->pci = pci;
	imx6_pcie->drvdata = of_device_get_match_data(dev);

	/* Find the PHY if one is defined, only imx7d uses it */
	np = of_parse_phandle(node, "fsl,imx7d-pcie-phy", 0);
	if (np) {
		struct resource res;

		ret = of_address_to_resource(np, 0, &res);
		if (ret) {
			dev_err(dev, "Unable to map PCIe PHY\n");
			return ret;
		}
		imx6_pcie->phy_base = devm_ioremap_resource(dev, &res);
		if (IS_ERR(imx6_pcie->phy_base)) {
			dev_err(dev, "Unable to map PCIe PHY\n");
			return PTR_ERR(imx6_pcie->phy_base);
		}
	}

	dbi_base = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pci->dbi_base = devm_ioremap_resource(dev, dbi_base);
	if (IS_ERR(pci->dbi_base))
		return PTR_ERR(pci->dbi_base);

	/* Fetch GPIOs */
	imx6_pcie->reset_gpio = of_get_named_gpio(node, "reset-gpio", 0);
	imx6_pcie->gpio_active_high = of_property_read_bool(node,
						"reset-gpio-active-high");
	if (gpio_is_valid(imx6_pcie->reset_gpio)) {
		ret = devm_gpio_request_one(dev, imx6_pcie->reset_gpio,
				imx6_pcie->gpio_active_high ?
					GPIOF_OUT_INIT_HIGH :
					GPIOF_OUT_INIT_LOW,
				"PCIe reset");
		if (ret) {
			dev_err(dev, "unable to get reset gpio\n");
			return ret;
		}
	} else if (imx6_pcie->reset_gpio == -EPROBE_DEFER) {
		return imx6_pcie->reset_gpio;
	}

	/* Fetch clocks */
	imx6_pcie->pcie_phy = devm_clk_get(dev, "pcie_phy");
	if (IS_ERR(imx6_pcie->pcie_phy)) {
		dev_err(dev, "pcie_phy clock source missing or invalid\n");
		return PTR_ERR(imx6_pcie->pcie_phy);
	}

	imx6_pcie->pcie_bus = devm_clk_get(dev, "pcie_bus");
	if (IS_ERR(imx6_pcie->pcie_bus)) {
		dev_err(dev, "pcie_bus clock source missing or invalid\n");
		return PTR_ERR(imx6_pcie->pcie_bus);
	}

	imx6_pcie->pcie = devm_clk_get(dev, "pcie");
	if (IS_ERR(imx6_pcie->pcie)) {
		dev_err(dev, "pcie clock source missing or invalid\n");
		return PTR_ERR(imx6_pcie->pcie);
	}

	switch (imx6_pcie->drvdata->variant) {
	case IMX6SX:
		imx6_pcie->pcie_inbound_axi = devm_clk_get(dev,
							   "pcie_inbound_axi");
		if (IS_ERR(imx6_pcie->pcie_inbound_axi)) {
			dev_err(dev, "pcie_inbound_axi clock missing or invalid\n");
			return PTR_ERR(imx6_pcie->pcie_inbound_axi);
		}
		break;
	case IMX8MQ:
		imx6_pcie->pcie_aux = devm_clk_get(dev, "pcie_aux");
		if (IS_ERR(imx6_pcie->pcie_aux)) {
			dev_err(dev, "pcie_aux clock source missing or invalid\n");
			return PTR_ERR(imx6_pcie->pcie_aux);
		}
		/* fall through */
	case IMX7D:
		if (dbi_base->start == IMX8MQ_PCIE2_BASE_ADDR)
			imx6_pcie->controller_id = 1;

		imx6_pcie->pciephy_reset = devm_reset_control_get_exclusive(dev,
									    "pciephy");
		if (IS_ERR(imx6_pcie->pciephy_reset)) {
			dev_err(dev, "Failed to get PCIEPHY reset control\n");
			return PTR_ERR(imx6_pcie->pciephy_reset);
		}

		imx6_pcie->apps_reset = devm_reset_control_get_exclusive(dev,
									 "apps");
		if (IS_ERR(imx6_pcie->apps_reset)) {
			dev_err(dev, "Failed to get PCIE APPS reset control\n");
			return PTR_ERR(imx6_pcie->apps_reset);
		}
		break;
	default:
		break;
	}

	/* Grab turnoff reset */
	imx6_pcie->turnoff_reset = devm_reset_control_get_optional_exclusive(dev, "turnoff");
	if (IS_ERR(imx6_pcie->turnoff_reset)) {
		dev_err(dev, "Failed to get TURNOFF reset control\n");
		return PTR_ERR(imx6_pcie->turnoff_reset);
	}

	/* Grab GPR config register range */
	imx6_pcie->iomuxc_gpr =
		 syscon_regmap_lookup_by_compatible("fsl,imx6q-iomuxc-gpr");
	if (IS_ERR(imx6_pcie->iomuxc_gpr)) {
		dev_err(dev, "unable to find iomuxc registers\n");
		return PTR_ERR(imx6_pcie->iomuxc_gpr);
	}

	/* Grab PCIe PHY Tx Settings */
	if (of_property_read_u32(node, "fsl,tx-deemph-gen1",
				 &imx6_pcie->tx_deemph_gen1))
		imx6_pcie->tx_deemph_gen1 = 0;

	if (of_property_read_u32(node, "fsl,tx-deemph-gen2-3p5db",
				 &imx6_pcie->tx_deemph_gen2_3p5db))
		imx6_pcie->tx_deemph_gen2_3p5db = 0;

	if (of_property_read_u32(node, "fsl,tx-deemph-gen2-6db",
				 &imx6_pcie->tx_deemph_gen2_6db))
		imx6_pcie->tx_deemph_gen2_6db = 20;

	if (of_property_read_u32(node, "fsl,tx-swing-full",
				 &imx6_pcie->tx_swing_full))
		imx6_pcie->tx_swing_full = 127;

	if (of_property_read_u32(node, "fsl,tx-swing-low",
				 &imx6_pcie->tx_swing_low))
		imx6_pcie->tx_swing_low = 127;

	/* Limit link speed */
	ret = of_property_read_u32(node, "fsl,max-link-speed",
				   &imx6_pcie->link_gen);
	if (ret)
		imx6_pcie->link_gen = 1;

	imx6_pcie->vpcie = devm_regulator_get_optional(&pdev->dev, "vpcie");
	if (IS_ERR(imx6_pcie->vpcie)) {
		if (PTR_ERR(imx6_pcie->vpcie) != -ENODEV)
			return PTR_ERR(imx6_pcie->vpcie);
		imx6_pcie->vpcie = NULL;
	}

	platform_set_drvdata(pdev, imx6_pcie);

	ret = imx6_pcie_attach_pd(dev);
	if (ret)
		return ret;

	ret = imx6_add_pcie_port(imx6_pcie, pdev);
	if (ret < 0)
		return ret;

	if (pci_msi_enabled()) {
		val = dw_pcie_readw_dbi(pci, PCIE_RC_IMX6_MSI_CAP +
					PCI_MSI_FLAGS);
		val |= PCI_MSI_FLAGS_ENABLE;
		dw_pcie_writew_dbi(pci, PCIE_RC_IMX6_MSI_CAP + PCI_MSI_FLAGS,
				   val);
	}

	return 0;
}