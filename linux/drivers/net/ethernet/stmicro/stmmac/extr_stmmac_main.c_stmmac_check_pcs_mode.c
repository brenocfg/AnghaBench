#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pcs; } ;
struct stmmac_priv {TYPE_1__* hw; int /*<<< orphan*/  dev; TYPE_3__ dma_cap; TYPE_2__* plat; } ;
struct TYPE_5__ {int interface; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcs; } ;

/* Variables and functions */
 int PHY_INTERFACE_MODE_RGMII ; 
 int PHY_INTERFACE_MODE_RGMII_ID ; 
 int PHY_INTERFACE_MODE_RGMII_RXID ; 
 int PHY_INTERFACE_MODE_RGMII_TXID ; 
 int PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  STMMAC_PCS_RGMII ; 
 int /*<<< orphan*/  STMMAC_PCS_SGMII ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void stmmac_check_pcs_mode(struct stmmac_priv *priv)
{
	int interface = priv->plat->interface;

	if (priv->dma_cap.pcs) {
		if ((interface == PHY_INTERFACE_MODE_RGMII) ||
		    (interface == PHY_INTERFACE_MODE_RGMII_ID) ||
		    (interface == PHY_INTERFACE_MODE_RGMII_RXID) ||
		    (interface == PHY_INTERFACE_MODE_RGMII_TXID)) {
			netdev_dbg(priv->dev, "PCS RGMII support enabled\n");
			priv->hw->pcs = STMMAC_PCS_RGMII;
		} else if (interface == PHY_INTERFACE_MODE_SGMII) {
			netdev_dbg(priv->dev, "PCS SGMII support enabled\n");
			priv->hw->pcs = STMMAC_PCS_SGMII;
		}
	}
}