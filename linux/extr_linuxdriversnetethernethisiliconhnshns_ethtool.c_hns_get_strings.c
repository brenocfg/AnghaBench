#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {TYPE_1__* phydev; } ;
struct hns_nic_priv {struct hnae_handle* ae_handle; } ;
struct hnae_handle {scalar_t__ phy_if; TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_strings ) (struct hnae_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  is_c45; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  ETH_SS_TEST ; 
 size_t MAC_INTERNALLOOP_MAC ; 
 size_t MAC_INTERNALLOOP_PHY ; 
 size_t MAC_INTERNALLOOP_SERDES ; 
 scalar_t__ PHY_INTERFACE_MODE_XGMII ; 
 int /*<<< orphan*/ * hns_nic_test_strs ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  stub1 (struct hnae_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_get_strings(struct net_device *netdev, u32 stringset, u8 *data)
{
	struct hns_nic_priv *priv = netdev_priv(netdev);
	struct hnae_handle *h = priv->ae_handle;
	char *buff = (char *)data;

	if (!h->dev->ops->get_strings) {
		netdev_err(netdev, "h->dev->ops->get_strings is null!\n");
		return;
	}

	if (stringset == ETH_SS_TEST) {
		if (priv->ae_handle->phy_if != PHY_INTERFACE_MODE_XGMII) {
			memcpy(buff, hns_nic_test_strs[MAC_INTERNALLOOP_MAC],
			       ETH_GSTRING_LEN);
			buff += ETH_GSTRING_LEN;
		}
		memcpy(buff, hns_nic_test_strs[MAC_INTERNALLOOP_SERDES],
		       ETH_GSTRING_LEN);
		buff += ETH_GSTRING_LEN;
		if ((netdev->phydev) && (!netdev->phydev->is_c45))
			memcpy(buff, hns_nic_test_strs[MAC_INTERNALLOOP_PHY],
			       ETH_GSTRING_LEN);

	} else {
		snprintf(buff, ETH_GSTRING_LEN, "rx_packets");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "tx_packets");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "rx_bytes");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "tx_bytes");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "rx_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "tx_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "rx_dropped");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "tx_dropped");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "multicast");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "collisions");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "rx_over_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "rx_crc_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "rx_frame_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "rx_fifo_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "rx_missed_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "tx_aborted_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "tx_carrier_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "tx_fifo_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "tx_heartbeat_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "rx_length_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "tx_window_errors");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "rx_compressed");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "tx_compressed");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "netdev_rx_dropped");
		buff = buff + ETH_GSTRING_LEN;
		snprintf(buff, ETH_GSTRING_LEN, "netdev_tx_dropped");
		buff = buff + ETH_GSTRING_LEN;

		snprintf(buff, ETH_GSTRING_LEN, "netdev_tx_timeout");
		buff = buff + ETH_GSTRING_LEN;

		h->dev->ops->get_strings(h, stringset, (u8 *)buff);
	}
}