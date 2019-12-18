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
struct net_device {int dummy; } ;
struct gswip_priv {int port_vlan_filter; } ;
struct dsa_switch {struct gswip_priv* priv; } ;
struct TYPE_2__ {struct net_device* bridge_dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 int GSWIP_PCE_PCTRL_0_TVM ; 
 int /*<<< orphan*/  GSWIP_PCE_PCTRL_0p (int) ; 
 int /*<<< orphan*/  GSWIP_PCE_VCTRL (int) ; 
 int GSWIP_PCE_VCTRL_UVR ; 
 int GSWIP_PCE_VCTRL_VEMR ; 
 int GSWIP_PCE_VCTRL_VIMR ; 
 int GSWIP_PCE_VCTRL_VSR ; 
 TYPE_1__* dsa_to_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  gswip_switch_mask (struct gswip_priv*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gswip_port_vlan_filtering(struct dsa_switch *ds, int port,
				     bool vlan_filtering)
{
	struct gswip_priv *priv = ds->priv;
	struct net_device *bridge = dsa_to_port(ds, port)->bridge_dev;

	/* Do not allow changing the VLAN filtering options while in bridge */
	if (!!(priv->port_vlan_filter & BIT(port)) != vlan_filtering && bridge)
		return -EIO;

	if (vlan_filtering) {
		/* Use port based VLAN tag */
		gswip_switch_mask(priv,
				  GSWIP_PCE_VCTRL_VSR,
				  GSWIP_PCE_VCTRL_UVR | GSWIP_PCE_VCTRL_VIMR |
				  GSWIP_PCE_VCTRL_VEMR,
				  GSWIP_PCE_VCTRL(port));
		gswip_switch_mask(priv, GSWIP_PCE_PCTRL_0_TVM, 0,
				  GSWIP_PCE_PCTRL_0p(port));
	} else {
		/* Use port based VLAN tag */
		gswip_switch_mask(priv,
				  GSWIP_PCE_VCTRL_UVR | GSWIP_PCE_VCTRL_VIMR |
				  GSWIP_PCE_VCTRL_VEMR,
				  GSWIP_PCE_VCTRL_VSR,
				  GSWIP_PCE_VCTRL(port));
		gswip_switch_mask(priv, 0, GSWIP_PCE_PCTRL_0_TVM,
				  GSWIP_PCE_PCTRL_0p(port));
	}

	return 0;
}