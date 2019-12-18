#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stmmac_resources {int /*<<< orphan*/  mac; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct plat_stmmacenet_data {int (* init ) (struct platform_device*,struct oxnas_dwmac*) ;struct oxnas_dwmac* bsp_priv; int /*<<< orphan*/  (* exit ) (struct platform_device*,struct oxnas_dwmac*) ;} ;
struct oxnas_dwmac {struct plat_stmmacenet_data* clk; struct plat_stmmacenet_data* regmap; TYPE_1__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct plat_stmmacenet_data*) ; 
 int PTR_ERR (struct plat_stmmacenet_data*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct plat_stmmacenet_data* devm_clk_get (TYPE_1__*,char*) ; 
 struct oxnas_dwmac* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxnas_dwmac_exit (struct platform_device*,struct oxnas_dwmac*) ; 
 int oxnas_dwmac_init (struct platform_device*,struct oxnas_dwmac*) ; 
 int stmmac_dvr_probe (TYPE_1__*,struct plat_stmmacenet_data*,struct stmmac_resources*) ; 
 int stmmac_get_platform_resources (struct platform_device*,struct stmmac_resources*) ; 
 struct plat_stmmacenet_data* stmmac_probe_config_dt (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_remove_config_dt (struct platform_device*,struct plat_stmmacenet_data*) ; 
 struct plat_stmmacenet_data* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int oxnas_dwmac_probe(struct platform_device *pdev)
{
	struct plat_stmmacenet_data *plat_dat;
	struct stmmac_resources stmmac_res;
	struct oxnas_dwmac *dwmac;
	int ret;

	ret = stmmac_get_platform_resources(pdev, &stmmac_res);
	if (ret)
		return ret;

	plat_dat = stmmac_probe_config_dt(pdev, &stmmac_res.mac);
	if (IS_ERR(plat_dat))
		return PTR_ERR(plat_dat);

	dwmac = devm_kzalloc(&pdev->dev, sizeof(*dwmac), GFP_KERNEL);
	if (!dwmac) {
		ret = -ENOMEM;
		goto err_remove_config_dt;
	}

	dwmac->dev = &pdev->dev;
	plat_dat->bsp_priv = dwmac;
	plat_dat->init = oxnas_dwmac_init;
	plat_dat->exit = oxnas_dwmac_exit;

	dwmac->regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							"oxsemi,sys-ctrl");
	if (IS_ERR(dwmac->regmap)) {
		dev_err(&pdev->dev, "failed to have sysctrl regmap\n");
		ret = PTR_ERR(dwmac->regmap);
		goto err_remove_config_dt;
	}

	dwmac->clk = devm_clk_get(&pdev->dev, "gmac");
	if (IS_ERR(dwmac->clk)) {
		ret = PTR_ERR(dwmac->clk);
		goto err_remove_config_dt;
	}

	ret = oxnas_dwmac_init(pdev, plat_dat->bsp_priv);
	if (ret)
		goto err_remove_config_dt;

	ret = stmmac_dvr_probe(&pdev->dev, plat_dat, &stmmac_res);
	if (ret)
		goto err_dwmac_exit;


	return 0;

err_dwmac_exit:
	oxnas_dwmac_exit(pdev, plat_dat->bsp_priv);
err_remove_config_dt:
	stmmac_remove_config_dt(pdev, plat_dat);

	return ret;
}