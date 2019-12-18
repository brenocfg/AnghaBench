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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {scalar_t__ asym_pause; scalar_t__ pause; int /*<<< orphan*/  advertising; int /*<<< orphan*/  duplex; } ;
struct mac_device {int rx_pause_req; int tx_pause_req; int /*<<< orphan*/  autoneg_pause; struct phy_device* phy_dev; } ;

/* Variables and functions */
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  LPA_PAUSE_ASYM ; 
 int /*<<< orphan*/  LPA_PAUSE_CAP ; 
 int /*<<< orphan*/  linkmode_adv_to_lcl_adv_t (int /*<<< orphan*/ ) ; 
 int mii_resolve_flowctrl_fdx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fman_get_pause_cfg(struct mac_device *mac_dev, bool *rx_pause,
			bool *tx_pause)
{
	struct phy_device *phy_dev = mac_dev->phy_dev;
	u16 lcl_adv, rmt_adv;
	u8 flowctrl;

	*rx_pause = *tx_pause = false;

	if (!phy_dev->duplex)
		return;

	/* If PAUSE autonegotiation is disabled, the TX/RX PAUSE settings
	 * are those set by ethtool.
	 */
	if (!mac_dev->autoneg_pause) {
		*rx_pause = mac_dev->rx_pause_req;
		*tx_pause = mac_dev->tx_pause_req;
		return;
	}

	/* Else if PAUSE autonegotiation is enabled, the TX/RX PAUSE
	 * settings depend on the result of the link negotiation.
	 */

	/* get local capabilities */
	lcl_adv = linkmode_adv_to_lcl_adv_t(phy_dev->advertising);

	/* get link partner capabilities */
	rmt_adv = 0;
	if (phy_dev->pause)
		rmt_adv |= LPA_PAUSE_CAP;
	if (phy_dev->asym_pause)
		rmt_adv |= LPA_PAUSE_ASYM;

	/* Calculate TX/RX settings based on local and peer advertised
	 * symmetric/asymmetric PAUSE capabilities.
	 */
	flowctrl = mii_resolve_flowctrl_fdx(lcl_adv, rmt_adv);
	if (flowctrl & FLOW_CTRL_RX)
		*rx_pause = true;
	if (flowctrl & FLOW_CTRL_TX)
		*tx_pause = true;
}