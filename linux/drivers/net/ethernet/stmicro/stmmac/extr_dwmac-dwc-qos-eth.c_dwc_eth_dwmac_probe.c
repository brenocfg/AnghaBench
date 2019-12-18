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
struct stmmac_resources {scalar_t__ irq; int wol_irq; void* addr; int /*<<< orphan*/  mac; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  void plat_stmmacenet_data ;
struct dwc_eth_dwmac_data {int /*<<< orphan*/  (* remove ) (struct platform_device*) ;void* (* probe ) (struct platform_device*,void*,struct stmmac_resources*) ;} ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int dwc_eth_dwmac_config_dt (struct platform_device*,void*) ; 
 int /*<<< orphan*/  memset (struct stmmac_resources*,int /*<<< orphan*/ ,int) ; 
 struct dwc_eth_dwmac_data* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int stmmac_dvr_probe (int /*<<< orphan*/ *,void*,struct stmmac_resources*) ; 
 void* stmmac_probe_config_dt (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_remove_config_dt (struct platform_device*,void*) ; 
 void* stub1 (struct platform_device*,void*,struct stmmac_resources*) ; 
 int /*<<< orphan*/  stub2 (struct platform_device*) ; 

__attribute__((used)) static int dwc_eth_dwmac_probe(struct platform_device *pdev)
{
	const struct dwc_eth_dwmac_data *data;
	struct plat_stmmacenet_data *plat_dat;
	struct stmmac_resources stmmac_res;
	void *priv;
	int ret;

	data = of_device_get_match_data(&pdev->dev);

	memset(&stmmac_res, 0, sizeof(struct stmmac_resources));

	/**
	 * Since stmmac_platform supports name IRQ only, basic platform
	 * resource initialization is done in the glue logic.
	 */
	stmmac_res.irq = platform_get_irq(pdev, 0);
	if (stmmac_res.irq < 0)
		return stmmac_res.irq;
	stmmac_res.wol_irq = stmmac_res.irq;

	stmmac_res.addr = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(stmmac_res.addr))
		return PTR_ERR(stmmac_res.addr);

	plat_dat = stmmac_probe_config_dt(pdev, &stmmac_res.mac);
	if (IS_ERR(plat_dat))
		return PTR_ERR(plat_dat);

	priv = data->probe(pdev, plat_dat, &stmmac_res);
	if (IS_ERR(priv)) {
		ret = PTR_ERR(priv);

		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to probe subdriver: %d\n",
				ret);

		goto remove_config;
	}

	ret = dwc_eth_dwmac_config_dt(pdev, plat_dat);
	if (ret)
		goto remove;

	ret = stmmac_dvr_probe(&pdev->dev, plat_dat, &stmmac_res);
	if (ret)
		goto remove;

	return ret;

remove:
	data->remove(pdev);
remove_config:
	stmmac_remove_config_dt(pdev, plat_dat);

	return ret;
}