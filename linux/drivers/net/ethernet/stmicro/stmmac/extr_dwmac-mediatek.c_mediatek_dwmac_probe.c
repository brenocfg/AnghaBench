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
struct plat_stmmacenet_data {int has_gmac4; int riwt_off; int /*<<< orphan*/  exit; int /*<<< orphan*/  (* init ) (struct platform_device*,struct mediatek_dwmac_plat_data*) ;struct mediatek_dwmac_plat_data* bsp_priv; int /*<<< orphan*/  maxmtu; scalar_t__ pmt; scalar_t__ has_gmac; int /*<<< orphan*/  interface; } ;
struct mediatek_dwmac_plat_data {int /*<<< orphan*/  phy_mode; int /*<<< orphan*/  np; TYPE_1__* dev; int /*<<< orphan*/  variant; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_DATA_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct plat_stmmacenet_data*) ; 
 int PTR_ERR (struct plat_stmmacenet_data*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct mediatek_dwmac_plat_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int mediatek_dwmac_clk_init (struct mediatek_dwmac_plat_data*) ; 
 int mediatek_dwmac_config_dt (struct mediatek_dwmac_plat_data*) ; 
 int /*<<< orphan*/  mediatek_dwmac_exit ; 
 int /*<<< orphan*/  mediatek_dwmac_init (struct platform_device*,struct mediatek_dwmac_plat_data*) ; 
 int /*<<< orphan*/  of_device_get_match_data (TYPE_1__*) ; 
 int stmmac_dvr_probe (TYPE_1__*,struct plat_stmmacenet_data*,struct stmmac_resources*) ; 
 int stmmac_get_platform_resources (struct platform_device*,struct stmmac_resources*) ; 
 struct plat_stmmacenet_data* stmmac_probe_config_dt (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_remove_config_dt (struct platform_device*,struct plat_stmmacenet_data*) ; 

__attribute__((used)) static int mediatek_dwmac_probe(struct platform_device *pdev)
{
	struct mediatek_dwmac_plat_data *priv_plat;
	struct plat_stmmacenet_data *plat_dat;
	struct stmmac_resources stmmac_res;
	int ret;

	priv_plat = devm_kzalloc(&pdev->dev, sizeof(*priv_plat), GFP_KERNEL);
	if (!priv_plat)
		return -ENOMEM;

	priv_plat->variant = of_device_get_match_data(&pdev->dev);
	if (!priv_plat->variant) {
		dev_err(&pdev->dev, "Missing dwmac-mediatek variant\n");
		return -EINVAL;
	}

	priv_plat->dev = &pdev->dev;
	priv_plat->np = pdev->dev.of_node;

	ret = mediatek_dwmac_config_dt(priv_plat);
	if (ret)
		return ret;

	ret = mediatek_dwmac_clk_init(priv_plat);
	if (ret)
		return ret;

	ret = stmmac_get_platform_resources(pdev, &stmmac_res);
	if (ret)
		return ret;

	plat_dat = stmmac_probe_config_dt(pdev, &stmmac_res.mac);
	if (IS_ERR(plat_dat))
		return PTR_ERR(plat_dat);

	plat_dat->interface = priv_plat->phy_mode;
	plat_dat->has_gmac4 = 1;
	plat_dat->has_gmac = 0;
	plat_dat->pmt = 0;
	plat_dat->riwt_off = 1;
	plat_dat->maxmtu = ETH_DATA_LEN;
	plat_dat->bsp_priv = priv_plat;
	plat_dat->init = mediatek_dwmac_init;
	plat_dat->exit = mediatek_dwmac_exit;
	mediatek_dwmac_init(pdev, priv_plat);

	ret = stmmac_dvr_probe(&pdev->dev, plat_dat, &stmmac_res);
	if (ret) {
		stmmac_remove_config_dt(pdev, plat_dat);
		return ret;
	}

	return 0;
}