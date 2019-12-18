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
typedef  int u32 ;
struct bcmgenet_priv {scalar_t__ crc_fwd_en; int /*<<< orphan*/  dev; } ;
typedef  enum bcmgenet_power_mode { ____Placeholder_bcmgenet_power_mode } bcmgenet_power_mode ;

/* Variables and functions */
 int CMD_CRC_FWD ; 
 int GENET_POWER_WOL_MAGIC ; 
 int MPD_EN ; 
 int /*<<< orphan*/  UMAC_CMD ; 
 int /*<<< orphan*/  UMAC_MPD_CTRL ; 
 int bcmgenet_umac_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_umac_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wol ; 

void bcmgenet_wol_power_up_cfg(struct bcmgenet_priv *priv,
			       enum bcmgenet_power_mode mode)
{
	u32 reg;

	if (mode != GENET_POWER_WOL_MAGIC) {
		netif_err(priv, wol, priv->dev, "invalid mode: %d\n", mode);
		return;
	}

	reg = bcmgenet_umac_readl(priv, UMAC_MPD_CTRL);
	if (!(reg & MPD_EN))
		return;	/* already powered up so skip the rest */
	reg &= ~MPD_EN;
	bcmgenet_umac_writel(priv, reg, UMAC_MPD_CTRL);

	/* Disable CRC Forward */
	reg = bcmgenet_umac_readl(priv, UMAC_CMD);
	reg &= ~CMD_CRC_FWD;
	bcmgenet_umac_writel(priv, reg, UMAC_CMD);
	priv->crc_fwd_en = 0;
}