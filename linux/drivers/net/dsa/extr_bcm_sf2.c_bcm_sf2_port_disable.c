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
typedef  int /*<<< orphan*/  u32 ;
struct dsa_switch {int dummy; } ;
struct TYPE_2__ {int num_gphy; } ;
struct bcm_sf2_priv {int wol_ports_mask; int moca_port; int int_phy_mask; TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CORE_DIS_LEARN ; 
 int /*<<< orphan*/  CORE_MEM_PSM_VDD_CTRL ; 
 int /*<<< orphan*/  P_TXQ_PSM_VDD (int) ; 
 int /*<<< orphan*/  b53_disable_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  bcm_sf2_gphy_enable_set (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  bcm_sf2_port_intr_disable (struct bcm_sf2_priv*,int) ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 int /*<<< orphan*/  core_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_writel (struct bcm_sf2_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sf2_port_disable(struct dsa_switch *ds, int port)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 reg;

	/* Disable learning while in WoL mode */
	if (priv->wol_ports_mask & (1 << port)) {
		reg = core_readl(priv, CORE_DIS_LEARN);
		reg |= BIT(port);
		core_writel(priv, reg, CORE_DIS_LEARN);
		return;
	}

	if (port == priv->moca_port)
		bcm_sf2_port_intr_disable(priv, port);

	if (priv->int_phy_mask & 1 << port && priv->hw_params.num_gphy == 1)
		bcm_sf2_gphy_enable_set(ds, false);

	b53_disable_port(ds, port);

	/* Power down the port memory */
	reg = core_readl(priv, CORE_MEM_PSM_VDD_CTRL);
	reg |= P_TXQ_PSM_VDD(port);
	core_writel(priv, reg, CORE_MEM_PSM_VDD_CTRL);
}