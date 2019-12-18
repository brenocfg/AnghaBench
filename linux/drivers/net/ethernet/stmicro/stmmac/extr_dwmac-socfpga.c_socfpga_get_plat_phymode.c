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
struct stmmac_priv {TYPE_1__* plat; } ;
struct socfpga_dwmac {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int interface; } ;

/* Variables and functions */
 struct net_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int socfpga_get_plat_phymode(struct socfpga_dwmac *dwmac)
{
	struct net_device *ndev = dev_get_drvdata(dwmac->dev);
	struct stmmac_priv *priv = netdev_priv(ndev);

	return priv->plat->interface;
}