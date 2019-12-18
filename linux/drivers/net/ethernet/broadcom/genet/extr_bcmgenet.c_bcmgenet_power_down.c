#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bcmgenet_priv {TYPE_2__* dev; TYPE_1__* hw_params; } ;
typedef  enum bcmgenet_power_mode { ____Placeholder_bcmgenet_power_mode } bcmgenet_power_mode ;
struct TYPE_4__ {int /*<<< orphan*/  phydev; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_EXT_PWR_MGMT ; 
 int EXT_IDDQ_GLBL_PWR ; 
 int EXT_PWR_DOWN_BIAS ; 
 int EXT_PWR_DOWN_DLL ; 
 int EXT_PWR_DOWN_PHY ; 
 int EXT_PWR_DOWN_PHY_EN ; 
 int EXT_PWR_DOWN_PHY_RD ; 
 int EXT_PWR_DOWN_PHY_RX ; 
 int EXT_PWR_DOWN_PHY_SD ; 
 int EXT_PWR_DOWN_PHY_TX ; 
 int GENET_HAS_EXT ; 
 int /*<<< orphan*/  GENET_IS_V5 (struct bcmgenet_priv*) ; 
#define  GENET_POWER_CABLE_SENSE 130 
#define  GENET_POWER_PASSIVE 129 
#define  GENET_POWER_WOL_MAGIC 128 
 int bcmgenet_ext_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_ext_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_phy_power_set (TYPE_2__*,int) ; 
 int bcmgenet_wol_power_down_cfg (struct bcmgenet_priv*,int) ; 
 int /*<<< orphan*/  phy_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcmgenet_power_down(struct bcmgenet_priv *priv,
				enum bcmgenet_power_mode mode)
{
	int ret = 0;
	u32 reg;

	switch (mode) {
	case GENET_POWER_CABLE_SENSE:
		phy_detach(priv->dev->phydev);
		break;

	case GENET_POWER_WOL_MAGIC:
		ret = bcmgenet_wol_power_down_cfg(priv, mode);
		break;

	case GENET_POWER_PASSIVE:
		/* Power down LED */
		if (priv->hw_params->flags & GENET_HAS_EXT) {
			reg = bcmgenet_ext_readl(priv, EXT_EXT_PWR_MGMT);
			if (GENET_IS_V5(priv))
				reg |= EXT_PWR_DOWN_PHY_EN |
				       EXT_PWR_DOWN_PHY_RD |
				       EXT_PWR_DOWN_PHY_SD |
				       EXT_PWR_DOWN_PHY_RX |
				       EXT_PWR_DOWN_PHY_TX |
				       EXT_IDDQ_GLBL_PWR;
			else
				reg |= EXT_PWR_DOWN_PHY;

			reg |= (EXT_PWR_DOWN_DLL | EXT_PWR_DOWN_BIAS);
			bcmgenet_ext_writel(priv, reg, EXT_EXT_PWR_MGMT);

			bcmgenet_phy_power_set(priv->dev, false);
		}
		break;
	default:
		break;
	}

	return ret;
}