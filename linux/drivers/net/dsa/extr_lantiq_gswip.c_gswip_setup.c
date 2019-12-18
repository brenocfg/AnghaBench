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
struct gswip_priv {int /*<<< orphan*/  dev; TYPE_1__* hw_info; } ;
struct dsa_switch {struct gswip_priv* priv; } ;
struct TYPE_2__ {unsigned int cpu_port; int max_ports; } ;

/* Variables and functions */
 scalar_t__ BIT (unsigned int) ; 
 int /*<<< orphan*/  GSWIP_BM_QUEUE_GCTRL ; 
 int /*<<< orphan*/  GSWIP_BM_QUEUE_GCTRL_GL_MOD ; 
 int /*<<< orphan*/  GSWIP_FDMA_PCTRL_STEN ; 
 int /*<<< orphan*/  GSWIP_FDMA_PCTRLp (unsigned int) ; 
 int /*<<< orphan*/  GSWIP_MAC_CTRL_2_MLEN ; 
 int /*<<< orphan*/  GSWIP_MAC_CTRL_2p (unsigned int) ; 
 int /*<<< orphan*/  GSWIP_MAC_FLEN ; 
 int /*<<< orphan*/  GSWIP_MDIO_GLOB ; 
 int GSWIP_MDIO_GLOB_ENABLE ; 
 int /*<<< orphan*/  GSWIP_MDIO_MDC_CFG0 ; 
 int /*<<< orphan*/  GSWIP_MDIO_MDC_CFG1 ; 
 int /*<<< orphan*/  GSWIP_MII_CFG_EN ; 
 int /*<<< orphan*/  GSWIP_PCE_GCTRL_0 ; 
 int /*<<< orphan*/  GSWIP_PCE_GCTRL_0_MTFL ; 
 int /*<<< orphan*/  GSWIP_PCE_GCTRL_0_VLAN ; 
 int /*<<< orphan*/  GSWIP_PCE_PCTRL_0_INGRESS ; 
 int /*<<< orphan*/  GSWIP_PCE_PCTRL_0p (unsigned int) ; 
 int /*<<< orphan*/  GSWIP_PCE_PMAP1 ; 
 int /*<<< orphan*/  GSWIP_PCE_PMAP2 ; 
 int /*<<< orphan*/  GSWIP_PCE_PMAP3 ; 
 int /*<<< orphan*/  GSWIP_SWRES ; 
 scalar_t__ GSWIP_SWRES_R0 ; 
 scalar_t__ VLAN_ETH_FRAME_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gswip_mdio_mask (struct gswip_priv*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_mdio_w (struct gswip_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_mii_mask_cfg (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gswip_pce_load_microcode (struct gswip_priv*) ; 
 int /*<<< orphan*/  gswip_port_disable (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  gswip_port_enable (struct dsa_switch*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gswip_port_vlan_filtering (struct dsa_switch*,int,int) ; 
 int /*<<< orphan*/  gswip_switch_mask (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gswip_switch_r_timeout (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_switch_w (struct gswip_priv*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int gswip_setup(struct dsa_switch *ds)
{
	struct gswip_priv *priv = ds->priv;
	unsigned int cpu_port = priv->hw_info->cpu_port;
	int i;
	int err;

	gswip_switch_w(priv, GSWIP_SWRES_R0, GSWIP_SWRES);
	usleep_range(5000, 10000);
	gswip_switch_w(priv, 0, GSWIP_SWRES);

	/* disable port fetch/store dma on all ports */
	for (i = 0; i < priv->hw_info->max_ports; i++) {
		gswip_port_disable(ds, i);
		gswip_port_vlan_filtering(ds, i, false);
	}

	/* enable Switch */
	gswip_mdio_mask(priv, 0, GSWIP_MDIO_GLOB_ENABLE, GSWIP_MDIO_GLOB);

	err = gswip_pce_load_microcode(priv);
	if (err) {
		dev_err(priv->dev, "writing PCE microcode failed, %i", err);
		return err;
	}

	/* Default unknown Broadcast/Multicast/Unicast port maps */
	gswip_switch_w(priv, BIT(cpu_port), GSWIP_PCE_PMAP1);
	gswip_switch_w(priv, BIT(cpu_port), GSWIP_PCE_PMAP2);
	gswip_switch_w(priv, BIT(cpu_port), GSWIP_PCE_PMAP3);

	/* disable PHY auto polling */
	gswip_mdio_w(priv, 0x0, GSWIP_MDIO_MDC_CFG0);
	/* Configure the MDIO Clock 2.5 MHz */
	gswip_mdio_mask(priv, 0xff, 0x09, GSWIP_MDIO_MDC_CFG1);

	/* Disable the xMII link */
	gswip_mii_mask_cfg(priv, GSWIP_MII_CFG_EN, 0, 0);
	gswip_mii_mask_cfg(priv, GSWIP_MII_CFG_EN, 0, 1);
	gswip_mii_mask_cfg(priv, GSWIP_MII_CFG_EN, 0, 5);

	/* enable special tag insertion on cpu port */
	gswip_switch_mask(priv, 0, GSWIP_FDMA_PCTRL_STEN,
			  GSWIP_FDMA_PCTRLp(cpu_port));

	/* accept special tag in ingress direction */
	gswip_switch_mask(priv, 0, GSWIP_PCE_PCTRL_0_INGRESS,
			  GSWIP_PCE_PCTRL_0p(cpu_port));

	gswip_switch_mask(priv, 0, GSWIP_MAC_CTRL_2_MLEN,
			  GSWIP_MAC_CTRL_2p(cpu_port));
	gswip_switch_w(priv, VLAN_ETH_FRAME_LEN + 8, GSWIP_MAC_FLEN);
	gswip_switch_mask(priv, 0, GSWIP_BM_QUEUE_GCTRL_GL_MOD,
			  GSWIP_BM_QUEUE_GCTRL);

	/* VLAN aware Switching */
	gswip_switch_mask(priv, 0, GSWIP_PCE_GCTRL_0_VLAN, GSWIP_PCE_GCTRL_0);

	/* Flush MAC Table */
	gswip_switch_mask(priv, 0, GSWIP_PCE_GCTRL_0_MTFL, GSWIP_PCE_GCTRL_0);

	err = gswip_switch_r_timeout(priv, GSWIP_PCE_GCTRL_0,
				     GSWIP_PCE_GCTRL_0_MTFL);
	if (err) {
		dev_err(priv->dev, "MAC flushing didn't finish\n");
		return err;
	}

	gswip_port_enable(ds, cpu_port, NULL);
	return 0;
}