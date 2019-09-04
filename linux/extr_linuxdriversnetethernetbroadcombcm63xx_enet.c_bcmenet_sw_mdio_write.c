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
typedef  int uint16_t ;
typedef  int u32 ;
struct bcm_enet_priv {int /*<<< orphan*/  enetsw_mdio_lock; } ;

/* Variables and functions */
 int ENETSW_MDIOC_EXT_MASK ; 
 int ENETSW_MDIOC_PHYID_SHIFT ; 
 int /*<<< orphan*/  ENETSW_MDIOC_REG ; 
 int ENETSW_MDIOC_REG_SHIFT ; 
 int ENETSW_MDIOC_WR_MASK ; 
 int /*<<< orphan*/  enetsw_writel (struct bcm_enet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bcmenet_sw_mdio_write(struct bcm_enet_priv *priv,
				 int ext, int phy_id, int location,
				 uint16_t data)
{
	u32 reg;

	spin_lock_bh(&priv->enetsw_mdio_lock);
	enetsw_writel(priv, 0, ENETSW_MDIOC_REG);

	reg = ENETSW_MDIOC_WR_MASK |
		(phy_id << ENETSW_MDIOC_PHYID_SHIFT) |
		(location << ENETSW_MDIOC_REG_SHIFT);

	if (ext)
		reg |= ENETSW_MDIOC_EXT_MASK;

	reg |= data;

	enetsw_writel(priv, reg, ENETSW_MDIOC_REG);
	udelay(50);
	spin_unlock_bh(&priv->enetsw_mdio_lock);
}