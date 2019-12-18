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
struct stmmac_priv {struct plat_stmmacenet_data* plat; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct plat_stmmacenet_data {int /*<<< orphan*/  bsp_priv; int /*<<< orphan*/  (* exit ) (struct platform_device*,int /*<<< orphan*/ ) ;} ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int stmmac_dvr_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_remove_config_dt (struct platform_device*,struct plat_stmmacenet_data*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*,int /*<<< orphan*/ ) ; 

int stmmac_pltfr_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct stmmac_priv *priv = netdev_priv(ndev);
	struct plat_stmmacenet_data *plat = priv->plat;
	int ret = stmmac_dvr_remove(&pdev->dev);

	if (plat->exit)
		plat->exit(pdev, plat->bsp_priv);

	stmmac_remove_config_dt(pdev, plat);

	return ret;
}