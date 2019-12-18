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
typedef  int /*<<< orphan*/  u32 ;
struct bcmgenet_priv {TYPE_2__* dev; TYPE_1__* hw_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  phydev; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int GENET_HAS_MOCA_LINK_DET ; 
 int /*<<< orphan*/  GENET_IS_V5 (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  LED_ACT_SOURCE_MAC ; 
 int /*<<< orphan*/  SYS_PORT_CTRL ; 
 int /*<<< orphan*/  bcmgenet_fixed_phy_link_update ; 
 int /*<<< orphan*/  bcmgenet_sys_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_sys_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_phy_set_link_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcmgenet_moca_phy_setup(struct bcmgenet_priv *priv)
{
	u32 reg;

	if (!GENET_IS_V5(priv)) {
		/* Speed settings are set in bcmgenet_mii_setup() */
		reg = bcmgenet_sys_readl(priv, SYS_PORT_CTRL);
		reg |= LED_ACT_SOURCE_MAC;
		bcmgenet_sys_writel(priv, reg, SYS_PORT_CTRL);
	}

	if (priv->hw_params->flags & GENET_HAS_MOCA_LINK_DET)
		fixed_phy_set_link_update(priv->dev->phydev,
					  bcmgenet_fixed_phy_link_update);
}