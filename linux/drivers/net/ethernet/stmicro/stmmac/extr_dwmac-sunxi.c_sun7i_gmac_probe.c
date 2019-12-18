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
struct sunxi_priv_data {struct plat_stmmacenet_data* regulator; struct plat_stmmacenet_data* tx_clk; int /*<<< orphan*/  interface; } ;
struct stmmac_resources {int /*<<< orphan*/  mac; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct plat_stmmacenet_data {int tx_coe; int has_gmac; int (* init ) (struct platform_device*,struct sunxi_priv_data*) ;struct sunxi_priv_data* bsp_priv; int /*<<< orphan*/  fix_mac_speed; int /*<<< orphan*/  (* exit ) (struct platform_device*,struct sunxi_priv_data*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct plat_stmmacenet_data*) ; 
 int PTR_ERR (struct plat_stmmacenet_data*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct plat_stmmacenet_data* devm_clk_get (struct device*,char*) ; 
 struct sunxi_priv_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct plat_stmmacenet_data* devm_regulator_get_optional (struct device*,char*) ; 
 int /*<<< orphan*/  of_get_phy_mode (int /*<<< orphan*/ ) ; 
 int stmmac_dvr_probe (struct device*,struct plat_stmmacenet_data*,struct stmmac_resources*) ; 
 int stmmac_get_platform_resources (struct platform_device*,struct stmmac_resources*) ; 
 struct plat_stmmacenet_data* stmmac_probe_config_dt (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_remove_config_dt (struct platform_device*,struct plat_stmmacenet_data*) ; 
 int /*<<< orphan*/  sun7i_fix_speed ; 
 int /*<<< orphan*/  sun7i_gmac_exit (struct platform_device*,struct sunxi_priv_data*) ; 
 int sun7i_gmac_init (struct platform_device*,struct sunxi_priv_data*) ; 

__attribute__((used)) static int sun7i_gmac_probe(struct platform_device *pdev)
{
	struct plat_stmmacenet_data *plat_dat;
	struct stmmac_resources stmmac_res;
	struct sunxi_priv_data *gmac;
	struct device *dev = &pdev->dev;
	int ret;

	ret = stmmac_get_platform_resources(pdev, &stmmac_res);
	if (ret)
		return ret;

	plat_dat = stmmac_probe_config_dt(pdev, &stmmac_res.mac);
	if (IS_ERR(plat_dat))
		return PTR_ERR(plat_dat);

	gmac = devm_kzalloc(dev, sizeof(*gmac), GFP_KERNEL);
	if (!gmac) {
		ret = -ENOMEM;
		goto err_remove_config_dt;
	}

	gmac->interface = of_get_phy_mode(dev->of_node);

	gmac->tx_clk = devm_clk_get(dev, "allwinner_gmac_tx");
	if (IS_ERR(gmac->tx_clk)) {
		dev_err(dev, "could not get tx clock\n");
		ret = PTR_ERR(gmac->tx_clk);
		goto err_remove_config_dt;
	}

	/* Optional regulator for PHY */
	gmac->regulator = devm_regulator_get_optional(dev, "phy");
	if (IS_ERR(gmac->regulator)) {
		if (PTR_ERR(gmac->regulator) == -EPROBE_DEFER) {
			ret = -EPROBE_DEFER;
			goto err_remove_config_dt;
		}
		dev_info(dev, "no regulator found\n");
		gmac->regulator = NULL;
	}

	/* platform data specifying hardware features and callbacks.
	 * hardware features were copied from Allwinner drivers. */
	plat_dat->tx_coe = 1;
	plat_dat->has_gmac = true;
	plat_dat->bsp_priv = gmac;
	plat_dat->init = sun7i_gmac_init;
	plat_dat->exit = sun7i_gmac_exit;
	plat_dat->fix_mac_speed = sun7i_fix_speed;

	ret = sun7i_gmac_init(pdev, plat_dat->bsp_priv);
	if (ret)
		goto err_remove_config_dt;

	ret = stmmac_dvr_probe(&pdev->dev, plat_dat, &stmmac_res);
	if (ret)
		goto err_gmac_exit;

	return 0;

err_gmac_exit:
	sun7i_gmac_exit(pdev, plat_dat->bsp_priv);
err_remove_config_dt:
	stmmac_remove_config_dt(pdev, plat_dat);

	return ret;
}