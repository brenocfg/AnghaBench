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
struct gswip_priv {int dummy; } ;
struct dsa_switch {struct gswip_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  GSWIP_FDMA_PCTRL_EN ; 
 int /*<<< orphan*/  GSWIP_FDMA_PCTRLp (int) ; 
 int /*<<< orphan*/  GSWIP_MDIO_MDC_CFG0 ; 
 int /*<<< orphan*/  GSWIP_MDIO_PHY_LINK_DOWN ; 
 int /*<<< orphan*/  GSWIP_MDIO_PHY_LINK_MASK ; 
 int /*<<< orphan*/  GSWIP_MDIO_PHYp (int) ; 
 int /*<<< orphan*/  GSWIP_SDMA_PCTRL_EN ; 
 int /*<<< orphan*/  GSWIP_SDMA_PCTRLp (int) ; 
 int /*<<< orphan*/  dsa_is_cpu_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  gswip_mdio_mask (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_switch_mask (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gswip_port_disable(struct dsa_switch *ds, int port)
{
	struct gswip_priv *priv = ds->priv;

	if (!dsa_is_user_port(ds, port))
		return;

	if (!dsa_is_cpu_port(ds, port)) {
		gswip_mdio_mask(priv, GSWIP_MDIO_PHY_LINK_DOWN,
				GSWIP_MDIO_PHY_LINK_MASK,
				GSWIP_MDIO_PHYp(port));
		/* Deactivate MDIO auto polling */
		gswip_mdio_mask(priv, BIT(port), 0, GSWIP_MDIO_MDC_CFG0);
	}

	gswip_switch_mask(priv, GSWIP_FDMA_PCTRL_EN, 0,
			  GSWIP_FDMA_PCTRLp(port));
	gswip_switch_mask(priv, GSWIP_SDMA_PCTRL_EN, 0,
			  GSWIP_SDMA_PCTRLp(port));
}