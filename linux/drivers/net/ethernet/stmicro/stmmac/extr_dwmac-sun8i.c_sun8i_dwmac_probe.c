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
struct sunxi_priv_data {TYPE_1__* variant; struct regmap* regmap_field; struct regmap* regulator; struct regmap* tx_clk; } ;
struct stmmac_resources {int /*<<< orphan*/  mac; } ;
struct stmmac_priv {int dummy; } ;
struct regmap {int interface; int tx_coe; int has_sun8i; int (* init ) (struct platform_device*,struct sunxi_priv_data*) ;struct sunxi_priv_data* bsp_priv; int /*<<< orphan*/  setup; int /*<<< orphan*/  (* exit ) (struct platform_device*,struct sunxi_priv_data*) ;int /*<<< orphan*/  rx_coe; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct plat_stmmacenet_data {int interface; int tx_coe; int has_sun8i; int (* init ) (struct platform_device*,struct sunxi_priv_data*) ;struct sunxi_priv_data* bsp_priv; int /*<<< orphan*/  setup; int /*<<< orphan*/  (* exit ) (struct platform_device*,struct sunxi_priv_data*) ;int /*<<< orphan*/  rx_coe; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ soc_has_internal_phy; int /*<<< orphan*/ * syscon_field; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  STMMAC_RX_COE_TYPE2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct regmap* devm_clk_get (struct device*,char*) ; 
 struct sunxi_priv_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_field_alloc (struct device*,struct regmap*,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regulator_get_optional (struct device*,char*) ; 
 int get_ephy_nodes (struct stmmac_priv*) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 int of_get_phy_mode (int /*<<< orphan*/ ) ; 
 int stmmac_dvr_probe (struct device*,struct regmap*,struct stmmac_resources*) ; 
 int stmmac_get_platform_resources (struct platform_device*,struct stmmac_resources*) ; 
 struct regmap* stmmac_probe_config_dt (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun8i_dwmac_exit (struct platform_device*,struct sunxi_priv_data*) ; 
 struct regmap* sun8i_dwmac_get_syscon_from_dev (int /*<<< orphan*/ ) ; 
 int sun8i_dwmac_init (struct platform_device*,struct sunxi_priv_data*) ; 
 int sun8i_dwmac_register_mdio_mux (struct stmmac_priv*) ; 
 int sun8i_dwmac_reset (struct stmmac_priv*) ; 
 int /*<<< orphan*/  sun8i_dwmac_setup ; 
 int /*<<< orphan*/  sun8i_dwmac_unset_syscon (struct sunxi_priv_data*) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sun8i_dwmac_probe(struct platform_device *pdev)
{
	struct plat_stmmacenet_data *plat_dat;
	struct stmmac_resources stmmac_res;
	struct sunxi_priv_data *gmac;
	struct device *dev = &pdev->dev;
	int ret;
	struct stmmac_priv *priv;
	struct net_device *ndev;
	struct regmap *regmap;

	ret = stmmac_get_platform_resources(pdev, &stmmac_res);
	if (ret)
		return ret;

	plat_dat = stmmac_probe_config_dt(pdev, &stmmac_res.mac);
	if (IS_ERR(plat_dat))
		return PTR_ERR(plat_dat);

	gmac = devm_kzalloc(dev, sizeof(*gmac), GFP_KERNEL);
	if (!gmac)
		return -ENOMEM;

	gmac->variant = of_device_get_match_data(&pdev->dev);
	if (!gmac->variant) {
		dev_err(&pdev->dev, "Missing dwmac-sun8i variant\n");
		return -EINVAL;
	}

	gmac->tx_clk = devm_clk_get(dev, "stmmaceth");
	if (IS_ERR(gmac->tx_clk)) {
		dev_err(dev, "Could not get TX clock\n");
		return PTR_ERR(gmac->tx_clk);
	}

	/* Optional regulator for PHY */
	gmac->regulator = devm_regulator_get_optional(dev, "phy");
	if (IS_ERR(gmac->regulator)) {
		if (PTR_ERR(gmac->regulator) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		dev_info(dev, "No regulator found\n");
		gmac->regulator = NULL;
	}

	/* The "GMAC clock control" register might be located in the
	 * CCU address range (on the R40), or the system control address
	 * range (on most other sun8i and later SoCs).
	 *
	 * The former controls most if not all clocks in the SoC. The
	 * latter has an SoC identification register, and on some SoCs,
	 * controls to map device specific SRAM to either the intended
	 * peripheral, or the CPU address space.
	 *
	 * In either case, there should be a coordinated and restricted
	 * method of accessing the register needed here. This is done by
	 * having the device export a custom regmap, instead of a generic
	 * syscon, which grants all access to all registers.
	 *
	 * To support old device trees, we fall back to using the syscon
	 * interface if possible.
	 */
	regmap = sun8i_dwmac_get_syscon_from_dev(pdev->dev.of_node);
	if (IS_ERR(regmap))
		regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							 "syscon");
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&pdev->dev, "Unable to map syscon: %d\n", ret);
		return ret;
	}

	gmac->regmap_field = devm_regmap_field_alloc(dev, regmap,
						     *gmac->variant->syscon_field);
	if (IS_ERR(gmac->regmap_field)) {
		ret = PTR_ERR(gmac->regmap_field);
		dev_err(dev, "Unable to map syscon register: %d\n", ret);
		return ret;
	}

	ret = of_get_phy_mode(dev->of_node);
	if (ret < 0)
		return -EINVAL;
	plat_dat->interface = ret;

	/* platform data specifying hardware features and callbacks.
	 * hardware features were copied from Allwinner drivers.
	 */
	plat_dat->rx_coe = STMMAC_RX_COE_TYPE2;
	plat_dat->tx_coe = 1;
	plat_dat->has_sun8i = true;
	plat_dat->bsp_priv = gmac;
	plat_dat->init = sun8i_dwmac_init;
	plat_dat->exit = sun8i_dwmac_exit;
	plat_dat->setup = sun8i_dwmac_setup;

	ret = sun8i_dwmac_init(pdev, plat_dat->bsp_priv);
	if (ret)
		return ret;

	ret = stmmac_dvr_probe(&pdev->dev, plat_dat, &stmmac_res);
	if (ret)
		goto dwmac_exit;

	ndev = dev_get_drvdata(&pdev->dev);
	priv = netdev_priv(ndev);
	/* The mux must be registered after parent MDIO
	 * so after stmmac_dvr_probe()
	 */
	if (gmac->variant->soc_has_internal_phy) {
		ret = get_ephy_nodes(priv);
		if (ret)
			goto dwmac_exit;
		ret = sun8i_dwmac_register_mdio_mux(priv);
		if (ret) {
			dev_err(&pdev->dev, "Failed to register mux\n");
			goto dwmac_mux;
		}
	} else {
		ret = sun8i_dwmac_reset(priv);
		if (ret)
			goto dwmac_exit;
	}

	return ret;
dwmac_mux:
	sun8i_dwmac_unset_syscon(gmac);
dwmac_exit:
	sun8i_dwmac_exit(pdev, plat_dat->bsp_priv);
return ret;
}