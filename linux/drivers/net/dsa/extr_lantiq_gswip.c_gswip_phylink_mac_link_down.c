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
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  GSWIP_MII_CFG_EN ; 
 int /*<<< orphan*/  gswip_mii_mask_cfg (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gswip_phylink_mac_link_down(struct dsa_switch *ds, int port,
					unsigned int mode,
					phy_interface_t interface)
{
	struct gswip_priv *priv = ds->priv;

	gswip_mii_mask_cfg(priv, GSWIP_MII_CFG_EN, 0, port);
}