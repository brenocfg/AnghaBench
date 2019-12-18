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
struct plat_stmmacenet_data {struct meson8b_dwmac* bsp_priv; } ;
struct meson8b_dwmac_data {int (* set_phy_mode ) (struct meson8b_dwmac*) ;} ;
struct meson8b_dwmac {int tx_delay_ns; struct meson8b_dwmac_data const* data; scalar_t__ phy_mode; TYPE_1__* dev; struct plat_stmmacenet_data* regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct plat_stmmacenet_data*) ; 
 int PTR_ERR (struct plat_stmmacenet_data*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct meson8b_dwmac* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct plat_stmmacenet_data* devm_platform_ioremap_resource (struct platform_device*,int) ; 
 int meson8b_init_prg_eth (struct meson8b_dwmac*) ; 
 int meson8b_init_rgmii_tx_clk (struct meson8b_dwmac*) ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 scalar_t__ of_get_phy_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int stmmac_dvr_probe (TYPE_1__*,struct plat_stmmacenet_data*,struct stmmac_resources*) ; 
 int stmmac_get_platform_resources (struct platform_device*,struct stmmac_resources*) ; 
 struct plat_stmmacenet_data* stmmac_probe_config_dt (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_remove_config_dt (struct platform_device*,struct plat_stmmacenet_data*) ; 
 int stub1 (struct meson8b_dwmac*) ; 

__attribute__((used)) static int meson8b_dwmac_probe(struct platform_device *pdev)
{
	struct plat_stmmacenet_data *plat_dat;
	struct stmmac_resources stmmac_res;
	struct meson8b_dwmac *dwmac;
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

	dwmac->data = (const struct meson8b_dwmac_data *)
		of_device_get_match_data(&pdev->dev);
	if (!dwmac->data) {
		ret = -EINVAL;
		goto err_remove_config_dt;
	}
	dwmac->regs = devm_platform_ioremap_resource(pdev, 1);
	if (IS_ERR(dwmac->regs)) {
		ret = PTR_ERR(dwmac->regs);
		goto err_remove_config_dt;
	}

	dwmac->dev = &pdev->dev;
	dwmac->phy_mode = of_get_phy_mode(pdev->dev.of_node);
	if ((int)dwmac->phy_mode < 0) {
		dev_err(&pdev->dev, "missing phy-mode property\n");
		ret = -EINVAL;
		goto err_remove_config_dt;
	}

	/* use 2ns as fallback since this value was previously hardcoded */
	if (of_property_read_u32(pdev->dev.of_node, "amlogic,tx-delay-ns",
				 &dwmac->tx_delay_ns))
		dwmac->tx_delay_ns = 2;

	ret = meson8b_init_rgmii_tx_clk(dwmac);
	if (ret)
		goto err_remove_config_dt;

	ret = dwmac->data->set_phy_mode(dwmac);
	if (ret)
		goto err_remove_config_dt;

	ret = meson8b_init_prg_eth(dwmac);
	if (ret)
		goto err_remove_config_dt;

	plat_dat->bsp_priv = dwmac;

	ret = stmmac_dvr_probe(&pdev->dev, plat_dat, &stmmac_res);
	if (ret)
		goto err_remove_config_dt;

	return 0;

err_remove_config_dt:
	stmmac_remove_config_dt(pdev, plat_dat);

	return ret;
}