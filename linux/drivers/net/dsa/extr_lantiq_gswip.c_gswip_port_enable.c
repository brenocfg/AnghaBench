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
typedef  int u32 ;
struct TYPE_2__ {int addr; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct gswip_priv {int dummy; } ;
struct dsa_switch {struct gswip_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  GSWIP_BM_PCFG_CNTEN ; 
 int /*<<< orphan*/  GSWIP_BM_PCFGp (int) ; 
 int GSWIP_FDMA_PCTRL_EN ; 
 int GSWIP_FDMA_PCTRL_VLANMOD_BOTH ; 
 int /*<<< orphan*/  GSWIP_FDMA_PCTRLp (int) ; 
 int /*<<< orphan*/  GSWIP_MDIO_MDC_CFG0 ; 
 int GSWIP_MDIO_PHY_ADDR_MASK ; 
 int GSWIP_MDIO_PHY_FCONRX_AUTO ; 
 int GSWIP_MDIO_PHY_FCONTX_AUTO ; 
 int GSWIP_MDIO_PHY_FDUP_AUTO ; 
 int GSWIP_MDIO_PHY_LINK_AUTO ; 
 int GSWIP_MDIO_PHY_SPEED_AUTO ; 
 int /*<<< orphan*/  GSWIP_MDIO_PHYp (int) ; 
 int GSWIP_SDMA_PCTRL_EN ; 
 int /*<<< orphan*/  GSWIP_SDMA_PCTRLp (int) ; 
 int /*<<< orphan*/  dsa_is_cpu_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 
 int gswip_add_single_port_br (struct gswip_priv*,int,int) ; 
 int /*<<< orphan*/  gswip_mdio_mask (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_mdio_w (struct gswip_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_switch_mask (struct gswip_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_switch_w (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gswip_port_enable(struct dsa_switch *ds, int port,
			     struct phy_device *phydev)
{
	struct gswip_priv *priv = ds->priv;
	int err;

	if (!dsa_is_user_port(ds, port))
		return 0;

	if (!dsa_is_cpu_port(ds, port)) {
		err = gswip_add_single_port_br(priv, port, true);
		if (err)
			return err;
	}

	/* RMON Counter Enable for port */
	gswip_switch_w(priv, GSWIP_BM_PCFG_CNTEN, GSWIP_BM_PCFGp(port));

	/* enable port fetch/store dma & VLAN Modification */
	gswip_switch_mask(priv, 0, GSWIP_FDMA_PCTRL_EN |
				   GSWIP_FDMA_PCTRL_VLANMOD_BOTH,
			 GSWIP_FDMA_PCTRLp(port));
	gswip_switch_mask(priv, 0, GSWIP_SDMA_PCTRL_EN,
			  GSWIP_SDMA_PCTRLp(port));

	if (!dsa_is_cpu_port(ds, port)) {
		u32 macconf = GSWIP_MDIO_PHY_LINK_AUTO |
			      GSWIP_MDIO_PHY_SPEED_AUTO |
			      GSWIP_MDIO_PHY_FDUP_AUTO |
			      GSWIP_MDIO_PHY_FCONTX_AUTO |
			      GSWIP_MDIO_PHY_FCONRX_AUTO |
			      (phydev->mdio.addr & GSWIP_MDIO_PHY_ADDR_MASK);

		gswip_mdio_w(priv, macconf, GSWIP_MDIO_PHYp(port));
		/* Activate MDIO auto polling */
		gswip_mdio_mask(priv, 0, BIT(port), GSWIP_MDIO_MDC_CFG0);
	}

	return 0;
}