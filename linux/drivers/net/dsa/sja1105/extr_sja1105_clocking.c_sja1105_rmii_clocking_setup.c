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
struct sja1105_private {TYPE_1__* ds; } ;
struct device {int dummy; } ;
typedef  scalar_t__ sja1105_mii_role_t ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ XMII_MAC ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int sja1105_cgu_idiv_config (struct sja1105_private*,int,int,int) ; 
 int sja1105_cgu_rmii_ext_tx_clk_config (struct sja1105_private*,int) ; 
 int sja1105_cgu_rmii_pll_config (struct sja1105_private*) ; 
 int sja1105_cgu_rmii_ref_clk_config (struct sja1105_private*,int) ; 

__attribute__((used)) static int sja1105_rmii_clocking_setup(struct sja1105_private *priv, int port,
				       sja1105_mii_role_t role)
{
	struct device *dev = priv->ds->dev;
	int rc;

	dev_dbg(dev, "Configuring RMII-%s clocking\n",
		(role == XMII_MAC) ? "MAC" : "PHY");
	/* AH1601.pdf chapter 2.5.1. Sources */
	if (role == XMII_MAC) {
		/* Configure and enable PLL1 for 50Mhz output */
		rc = sja1105_cgu_rmii_pll_config(priv);
		if (rc < 0)
			return rc;
	}
	/* Disable IDIV for this port */
	rc = sja1105_cgu_idiv_config(priv, port, false, 1);
	if (rc < 0)
		return rc;
	/* Source to sink mappings */
	rc = sja1105_cgu_rmii_ref_clk_config(priv, port);
	if (rc < 0)
		return rc;
	if (role == XMII_MAC) {
		rc = sja1105_cgu_rmii_ext_tx_clk_config(priv, port);
		if (rc < 0)
			return rc;
	}
	return 0;
}