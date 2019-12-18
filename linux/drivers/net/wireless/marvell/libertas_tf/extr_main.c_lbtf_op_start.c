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
struct lbtf_private {int mac_control; int /*<<< orphan*/  radioon; int /*<<< orphan*/  capability; } ;
struct ieee80211_hw {struct lbtf_private* priv; } ;

/* Variables and functions */
 int CMD_ACT_MAC_RX_ON ; 
 int CMD_ACT_MAC_TX_ON ; 
 int /*<<< orphan*/  LBTF_DEB_MACOPS ; 
 int /*<<< orphan*/  RADIO_ON ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_set_mac_control (struct lbtf_private*) ; 
 int /*<<< orphan*/  lbtf_set_radio_control (struct lbtf_private*) ; 

__attribute__((used)) static int lbtf_op_start(struct ieee80211_hw *hw)
{
	struct lbtf_private *priv = hw->priv;

	lbtf_deb_enter(LBTF_DEB_MACOPS);

	priv->capability = WLAN_CAPABILITY_SHORT_PREAMBLE;
	priv->radioon = RADIO_ON;
	priv->mac_control = CMD_ACT_MAC_RX_ON | CMD_ACT_MAC_TX_ON;
	lbtf_set_mac_control(priv);
	lbtf_set_radio_control(priv);

	lbtf_deb_leave(LBTF_DEB_MACOPS);
	return 0;
}