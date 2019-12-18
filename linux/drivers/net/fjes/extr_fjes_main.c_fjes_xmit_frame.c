#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {char* data; int len; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct fjes_hw {int my_epid; int max_epid; TYPE_4__* ep_shm_info; } ;
struct TYPE_6__ {int tx_packets; int tx_bytes; int tx_carrier_errors; int tx_dropped; int tx_errors; int tx_fifo_errors; } ;
struct fjes_adapter {int tx_retry_count; TYPE_2__ stats64; int /*<<< orphan*/  tx_stall_task; int /*<<< orphan*/  txrx_wq; scalar_t__ tx_start_jiffies; struct fjes_hw hw; } ;
struct ethhdr {int* h_dest; } ;
typedef  scalar_t__ netdev_tx_t ;
typedef  enum ep_partner_status { ____Placeholder_ep_partner_status } ep_partner_status ;
struct TYPE_7__ {int tx_packets; int tx_bytes; int tx_carrier_errors; int tx_dropped; int tx_errors; int tx_fifo_errors; } ;
struct TYPE_5__ {int tx_dropped_not_shared; int tx_dropped_ver_mismatch; int tx_dropped_buf_size_mismatch; int tx_dropped_vlanid_mismatch; int tx_buffer_full; } ;
struct TYPE_8__ {TYPE_3__ net_stats; TYPE_1__ ep_stats; int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int EP_PARTNER_SHARED ; 
 int ETH_ALEN ; 
 long FJES_TX_RETRY_TIMEOUT ; 
 scalar_t__ NETDEV_TX_BUSY ; 
 scalar_t__ NETDEV_TX_OK ; 
 int VLAN_ETH_HLEN ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  fjes_hw_check_epbuf_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fjes_hw_check_mtu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fjes_hw_check_vlan_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fjes_hw_get_partner_ep_status (struct fjes_hw*,int) ; 
 scalar_t__ fjes_tx_send (struct fjes_adapter*,int,char*,int) ; 
 scalar_t__ is_local_ether_addr (int*) ; 
 scalar_t__ is_multicast_ether_addr (int*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct fjes_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vlan_get_tag (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t
fjes_xmit_frame(struct sk_buff *skb, struct net_device *netdev)
{
	struct fjes_adapter *adapter = netdev_priv(netdev);
	struct fjes_hw *hw = &adapter->hw;

	int max_epid, my_epid, dest_epid;
	enum ep_partner_status pstatus;
	struct netdev_queue *cur_queue;
	char shortpkt[VLAN_ETH_HLEN];
	bool is_multi, vlan;
	struct ethhdr *eth;
	u16 queue_no = 0;
	u16 vlan_id = 0;
	netdev_tx_t ret;
	char *data;
	int len;

	ret = NETDEV_TX_OK;
	is_multi = false;
	cur_queue = netdev_get_tx_queue(netdev, queue_no);

	eth = (struct ethhdr *)skb->data;
	my_epid = hw->my_epid;

	vlan = (vlan_get_tag(skb, &vlan_id) == 0) ? true : false;

	data = skb->data;
	len = skb->len;

	if (is_multicast_ether_addr(eth->h_dest)) {
		dest_epid = 0;
		max_epid = hw->max_epid;
		is_multi = true;
	} else if (is_local_ether_addr(eth->h_dest)) {
		dest_epid = eth->h_dest[ETH_ALEN - 1];
		max_epid = dest_epid + 1;

		if ((eth->h_dest[0] == 0x02) &&
		    (0x00 == (eth->h_dest[1] | eth->h_dest[2] |
			      eth->h_dest[3] | eth->h_dest[4])) &&
		    (dest_epid < hw->max_epid)) {
			;
		} else {
			dest_epid = 0;
			max_epid = 0;
			ret = NETDEV_TX_OK;

			adapter->stats64.tx_packets += 1;
			hw->ep_shm_info[my_epid].net_stats.tx_packets += 1;
			adapter->stats64.tx_bytes += len;
			hw->ep_shm_info[my_epid].net_stats.tx_bytes += len;
		}
	} else {
		dest_epid = 0;
		max_epid = 0;
		ret = NETDEV_TX_OK;

		adapter->stats64.tx_packets += 1;
		hw->ep_shm_info[my_epid].net_stats.tx_packets += 1;
		adapter->stats64.tx_bytes += len;
		hw->ep_shm_info[my_epid].net_stats.tx_bytes += len;
	}

	for (; dest_epid < max_epid; dest_epid++) {
		if (my_epid == dest_epid)
			continue;

		pstatus = fjes_hw_get_partner_ep_status(hw, dest_epid);
		if (pstatus != EP_PARTNER_SHARED) {
			if (!is_multi)
				hw->ep_shm_info[dest_epid].ep_stats
					.tx_dropped_not_shared += 1;
			ret = NETDEV_TX_OK;
		} else if (!fjes_hw_check_epbuf_version(
				&adapter->hw.ep_shm_info[dest_epid].rx, 0)) {
			/* version is NOT 0 */
			adapter->stats64.tx_carrier_errors += 1;
			hw->ep_shm_info[dest_epid].net_stats
						.tx_carrier_errors += 1;
			hw->ep_shm_info[dest_epid].ep_stats
					.tx_dropped_ver_mismatch += 1;

			ret = NETDEV_TX_OK;
		} else if (!fjes_hw_check_mtu(
				&adapter->hw.ep_shm_info[dest_epid].rx,
				netdev->mtu)) {
			adapter->stats64.tx_dropped += 1;
			hw->ep_shm_info[dest_epid].net_stats.tx_dropped += 1;
			adapter->stats64.tx_errors += 1;
			hw->ep_shm_info[dest_epid].net_stats.tx_errors += 1;
			hw->ep_shm_info[dest_epid].ep_stats
					.tx_dropped_buf_size_mismatch += 1;

			ret = NETDEV_TX_OK;
		} else if (vlan &&
			   !fjes_hw_check_vlan_id(
				&adapter->hw.ep_shm_info[dest_epid].rx,
				vlan_id)) {
			hw->ep_shm_info[dest_epid].ep_stats
				.tx_dropped_vlanid_mismatch += 1;
			ret = NETDEV_TX_OK;
		} else {
			if (len < VLAN_ETH_HLEN) {
				memset(shortpkt, 0, VLAN_ETH_HLEN);
				memcpy(shortpkt, skb->data, skb->len);
				len = VLAN_ETH_HLEN;
				data = shortpkt;
			}

			if (adapter->tx_retry_count == 0) {
				adapter->tx_start_jiffies = jiffies;
				adapter->tx_retry_count = 1;
			} else {
				adapter->tx_retry_count++;
			}

			if (fjes_tx_send(adapter, dest_epid, data, len)) {
				if (is_multi) {
					ret = NETDEV_TX_OK;
				} else if (
					   ((long)jiffies -
					    (long)adapter->tx_start_jiffies) >=
					    FJES_TX_RETRY_TIMEOUT) {
					adapter->stats64.tx_fifo_errors += 1;
					hw->ep_shm_info[dest_epid].net_stats
								.tx_fifo_errors += 1;
					adapter->stats64.tx_errors += 1;
					hw->ep_shm_info[dest_epid].net_stats
								.tx_errors += 1;

					ret = NETDEV_TX_OK;
				} else {
					netif_trans_update(netdev);
					hw->ep_shm_info[dest_epid].ep_stats
						.tx_buffer_full += 1;
					netif_tx_stop_queue(cur_queue);

					if (!work_pending(&adapter->tx_stall_task))
						queue_work(adapter->txrx_wq,
							   &adapter->tx_stall_task);

					ret = NETDEV_TX_BUSY;
				}
			} else {
				if (!is_multi) {
					adapter->stats64.tx_packets += 1;
					hw->ep_shm_info[dest_epid].net_stats
								.tx_packets += 1;
					adapter->stats64.tx_bytes += len;
					hw->ep_shm_info[dest_epid].net_stats
								.tx_bytes += len;
				}

				adapter->tx_retry_count = 0;
				ret = NETDEV_TX_OK;
			}
		}
	}

	if (ret == NETDEV_TX_OK) {
		dev_kfree_skb(skb);
		if (is_multi) {
			adapter->stats64.tx_packets += 1;
			hw->ep_shm_info[my_epid].net_stats.tx_packets += 1;
			adapter->stats64.tx_bytes += 1;
			hw->ep_shm_info[my_epid].net_stats.tx_bytes += len;
		}
	}

	return ret;
}