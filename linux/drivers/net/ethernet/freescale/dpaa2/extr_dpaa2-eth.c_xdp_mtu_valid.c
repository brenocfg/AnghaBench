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
struct dpaa2_eth_priv {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int DPAA2_ETH_L2_MAX_FRM (int) ; 
 int DPAA2_ETH_RX_BUF_SIZE ; 
 int DPAA2_ETH_RX_HWA_SIZE ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 int XDP_PACKET_HEADROOM ; 
 int dpaa2_eth_rx_head_room (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static bool xdp_mtu_valid(struct dpaa2_eth_priv *priv, int mtu)
{
	int mfl, linear_mfl;

	mfl = DPAA2_ETH_L2_MAX_FRM(mtu);
	linear_mfl = DPAA2_ETH_RX_BUF_SIZE - DPAA2_ETH_RX_HWA_SIZE -
		     dpaa2_eth_rx_head_room(priv) - XDP_PACKET_HEADROOM;

	if (mfl > linear_mfl) {
		netdev_warn(priv->net_dev, "Maximum MTU for XDP is %d\n",
			    linear_mfl - VLAN_ETH_HLEN);
		return false;
	}

	return true;
}