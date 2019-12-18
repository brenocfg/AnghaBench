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
struct sja1105_private {int* rgmii_rx_delay; int* rgmii_tx_delay; TYPE_1__* info; } ;
struct sja1105_dt_port {scalar_t__ role; scalar_t__ phy_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  setup_rgmii_delay; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_RXID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 int SJA1105_NUM_PORTS ; 
 scalar_t__ XMII_MAC ; 

__attribute__((used)) static int sja1105_parse_rgmii_delays(struct sja1105_private *priv,
				      const struct sja1105_dt_port *ports)
{
	int i;

	for (i = 0; i < SJA1105_NUM_PORTS; i++) {
		if (ports->role == XMII_MAC)
			continue;

		if (ports->phy_mode == PHY_INTERFACE_MODE_RGMII_RXID ||
		    ports->phy_mode == PHY_INTERFACE_MODE_RGMII_ID)
			priv->rgmii_rx_delay[i] = true;

		if (ports->phy_mode == PHY_INTERFACE_MODE_RGMII_TXID ||
		    ports->phy_mode == PHY_INTERFACE_MODE_RGMII_ID)
			priv->rgmii_tx_delay[i] = true;

		if ((priv->rgmii_rx_delay[i] || priv->rgmii_tx_delay[i]) &&
		     !priv->info->setup_rgmii_delay)
			return -EINVAL;
	}
	return 0;
}