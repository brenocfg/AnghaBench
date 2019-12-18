#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct fjes_hw {int max_epid; int my_epid; TYPE_2__* ep_shm_info; } ;
struct fjes_adapter {struct fjes_hw hw; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_7__ {int stat_offset; int sizeof_stat; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_dropped_vlanid_mismatch; int /*<<< orphan*/  tx_dropped_buf_size_mismatch; int /*<<< orphan*/  tx_dropped_ver_mismatch; int /*<<< orphan*/  tx_dropped_not_shared; int /*<<< orphan*/  tx_buffer_full; int /*<<< orphan*/  recv_intr_zoneupdate; int /*<<< orphan*/  recv_intr_stop; int /*<<< orphan*/  recv_intr_unshare; int /*<<< orphan*/  recv_intr_rx; int /*<<< orphan*/  send_intr_zoneupdate; int /*<<< orphan*/  send_intr_unshare; int /*<<< orphan*/  send_intr_rx; int /*<<< orphan*/  com_unregist_buf_exec; int /*<<< orphan*/  com_regist_buf_exec; } ;
struct TYPE_6__ {TYPE_1__ ep_stats; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 TYPE_3__* fjes_gstrings_stats ; 
 struct fjes_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fjes_get_ethtool_stats(struct net_device *netdev,
				   struct ethtool_stats *stats, u64 *data)
{
	struct fjes_adapter *adapter = netdev_priv(netdev);
	struct fjes_hw *hw = &adapter->hw;
	int epidx;
	char *p;
	int i;

	for (i = 0; i < ARRAY_SIZE(fjes_gstrings_stats); i++) {
		p = (char *)adapter + fjes_gstrings_stats[i].stat_offset;
		data[i] = (fjes_gstrings_stats[i].sizeof_stat == sizeof(u64))
			? *(u64 *)p : *(u32 *)p;
	}
	for (epidx = 0; epidx < hw->max_epid; epidx++) {
		if (epidx == hw->my_epid)
			continue;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.com_regist_buf_exec;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.com_unregist_buf_exec;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.send_intr_rx;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.send_intr_unshare;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.send_intr_zoneupdate;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.recv_intr_rx;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.recv_intr_unshare;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.recv_intr_stop;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.recv_intr_zoneupdate;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.tx_buffer_full;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dropped_not_shared;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dropped_ver_mismatch;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dropped_buf_size_mismatch;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dropped_vlanid_mismatch;
	}
}