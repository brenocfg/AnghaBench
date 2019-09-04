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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct ctx_hw_stats {int dummy; } ;
struct bnxt_cp_ring_info {TYPE_1__* hw_stats; scalar_t__ rx_l4_csum_errors; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {size_t cp_nr_rings; int flags; scalar_t__ hw_rx_port_stats_ext; scalar_t__ hw_rx_port_stats; struct bnxt_napi** bnapi; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_8__ {int offset; } ;
struct TYPE_7__ {int offset; } ;
struct TYPE_6__ {scalar_t__ counter; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_discard_pkts; int /*<<< orphan*/  rx_discard_pkts; } ;

/* Variables and functions */
 int BNXT_FLAG_PORT_STATS ; 
 int BNXT_FLAG_PORT_STATS_EXT ; 
 size_t BNXT_NUM_PORT_STATS ; 
 size_t BNXT_NUM_PORT_STATS_EXT ; 
 size_t BNXT_NUM_SW_FUNC_STATS ; 
 size_t RX_TOTAL_DISCARDS ; 
 size_t TX_TOTAL_DISCARDS ; 
 TYPE_4__* bnxt_port_stats_arr ; 
 TYPE_3__* bnxt_port_stats_ext_arr ; 
 TYPE_2__* bnxt_sw_func_stats ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bnxt_get_ethtool_stats(struct net_device *dev,
				   struct ethtool_stats *stats, u64 *buf)
{
	u32 i, j = 0;
	struct bnxt *bp = netdev_priv(dev);
	u32 stat_fields = sizeof(struct ctx_hw_stats) / 8;

	if (!bp->bnapi)
		return;

	for (i = 0; i < BNXT_NUM_SW_FUNC_STATS; i++)
		bnxt_sw_func_stats[i].counter = 0;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		__le64 *hw_stats = (__le64 *)cpr->hw_stats;
		int k;

		for (k = 0; k < stat_fields; j++, k++)
			buf[j] = le64_to_cpu(hw_stats[k]);
		buf[j++] = cpr->rx_l4_csum_errors;

		bnxt_sw_func_stats[RX_TOTAL_DISCARDS].counter +=
			le64_to_cpu(cpr->hw_stats->rx_discard_pkts);
		bnxt_sw_func_stats[TX_TOTAL_DISCARDS].counter +=
			le64_to_cpu(cpr->hw_stats->tx_discard_pkts);
	}

	for (i = 0; i < BNXT_NUM_SW_FUNC_STATS; i++, j++)
		buf[j] = bnxt_sw_func_stats[i].counter;

	if (bp->flags & BNXT_FLAG_PORT_STATS) {
		__le64 *port_stats = (__le64 *)bp->hw_rx_port_stats;

		for (i = 0; i < BNXT_NUM_PORT_STATS; i++, j++) {
			buf[j] = le64_to_cpu(*(port_stats +
					       bnxt_port_stats_arr[i].offset));
		}
	}
	if (bp->flags & BNXT_FLAG_PORT_STATS_EXT) {
		__le64 *port_stats_ext = (__le64 *)bp->hw_rx_port_stats_ext;

		for (i = 0; i < BNXT_NUM_PORT_STATS_EXT; i++, j++) {
			buf[j] = le64_to_cpu(*(port_stats_ext +
					    bnxt_port_stats_ext_arr[i].offset));
		}
	}
}