#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct bnxt_cp_ring_info {TYPE_1__* hw_stats; scalar_t__ missed_irqs; scalar_t__ rx_l4_csum_errors; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {size_t cp_nr_rings; int flags; size_t fw_rx_stats_ext_size; size_t fw_tx_stats_ext_size; long* pri2cos; scalar_t__ hw_pcie_stats; scalar_t__ pri2cos_valid; scalar_t__ hw_tx_port_stats_ext; scalar_t__ hw_rx_port_stats_ext; scalar_t__ hw_rx_port_stats; struct bnxt_napi** bnapi; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_20__ {int offset; } ;
struct TYPE_19__ {int offset; } ;
struct TYPE_18__ {long base_off; } ;
struct TYPE_17__ {long base_off; } ;
struct TYPE_16__ {scalar_t__ counter; } ;
struct TYPE_15__ {long base_off; } ;
struct TYPE_14__ {long base_off; } ;
struct TYPE_13__ {int offset; } ;
struct TYPE_12__ {int /*<<< orphan*/  tx_discard_pkts; int /*<<< orphan*/  rx_discard_pkts; } ;
struct TYPE_11__ {int offset; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BNXT_FLAG_PCIE_STATS ; 
 int BNXT_FLAG_PORT_STATS ; 
 int BNXT_FLAG_PORT_STATS_EXT ; 
 size_t BNXT_NUM_PCIE_STATS ; 
 size_t BNXT_NUM_PORT_STATS ; 
 size_t BNXT_NUM_SW_FUNC_STATS ; 
 size_t RX_TOTAL_DISCARDS ; 
 size_t TX_TOTAL_DISCARDS ; 
 scalar_t__ bnxt_get_num_ring_stats (struct bnxt*) ; 
 size_t bnxt_get_num_tpa_ring_stats (struct bnxt*) ; 
 TYPE_10__* bnxt_pcie_stats_arr ; 
 TYPE_9__* bnxt_port_stats_arr ; 
 TYPE_8__* bnxt_port_stats_ext_arr ; 
 int /*<<< orphan*/  bnxt_ring_stats_str ; 
 TYPE_7__* bnxt_rx_bytes_pri_arr ; 
 TYPE_6__* bnxt_rx_pkts_pri_arr ; 
 TYPE_5__* bnxt_sw_func_stats ; 
 TYPE_4__* bnxt_tx_bytes_pri_arr ; 
 TYPE_3__* bnxt_tx_pkts_pri_arr ; 
 TYPE_2__* bnxt_tx_port_stats_ext_arr ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bnxt_get_ethtool_stats(struct net_device *dev,
				   struct ethtool_stats *stats, u64 *buf)
{
	u32 i, j = 0;
	struct bnxt *bp = netdev_priv(dev);
	u32 stat_fields = ARRAY_SIZE(bnxt_ring_stats_str) +
			  bnxt_get_num_tpa_ring_stats(bp);

	if (!bp->bnapi) {
		j += bnxt_get_num_ring_stats(bp) + BNXT_NUM_SW_FUNC_STATS;
		goto skip_ring_stats;
	}

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
		buf[j++] = cpr->missed_irqs;

		bnxt_sw_func_stats[RX_TOTAL_DISCARDS].counter +=
			le64_to_cpu(cpr->hw_stats->rx_discard_pkts);
		bnxt_sw_func_stats[TX_TOTAL_DISCARDS].counter +=
			le64_to_cpu(cpr->hw_stats->tx_discard_pkts);
	}

	for (i = 0; i < BNXT_NUM_SW_FUNC_STATS; i++, j++)
		buf[j] = bnxt_sw_func_stats[i].counter;

skip_ring_stats:
	if (bp->flags & BNXT_FLAG_PORT_STATS) {
		__le64 *port_stats = (__le64 *)bp->hw_rx_port_stats;

		for (i = 0; i < BNXT_NUM_PORT_STATS; i++, j++) {
			buf[j] = le64_to_cpu(*(port_stats +
					       bnxt_port_stats_arr[i].offset));
		}
	}
	if (bp->flags & BNXT_FLAG_PORT_STATS_EXT) {
		__le64 *rx_port_stats_ext = (__le64 *)bp->hw_rx_port_stats_ext;
		__le64 *tx_port_stats_ext = (__le64 *)bp->hw_tx_port_stats_ext;

		for (i = 0; i < bp->fw_rx_stats_ext_size; i++, j++) {
			buf[j] = le64_to_cpu(*(rx_port_stats_ext +
					    bnxt_port_stats_ext_arr[i].offset));
		}
		for (i = 0; i < bp->fw_tx_stats_ext_size; i++, j++) {
			buf[j] = le64_to_cpu(*(tx_port_stats_ext +
					bnxt_tx_port_stats_ext_arr[i].offset));
		}
		if (bp->pri2cos_valid) {
			for (i = 0; i < 8; i++, j++) {
				long n = bnxt_rx_bytes_pri_arr[i].base_off +
					 bp->pri2cos[i];

				buf[j] = le64_to_cpu(*(rx_port_stats_ext + n));
			}
			for (i = 0; i < 8; i++, j++) {
				long n = bnxt_rx_pkts_pri_arr[i].base_off +
					 bp->pri2cos[i];

				buf[j] = le64_to_cpu(*(rx_port_stats_ext + n));
			}
			for (i = 0; i < 8; i++, j++) {
				long n = bnxt_tx_bytes_pri_arr[i].base_off +
					 bp->pri2cos[i];

				buf[j] = le64_to_cpu(*(tx_port_stats_ext + n));
			}
			for (i = 0; i < 8; i++, j++) {
				long n = bnxt_tx_pkts_pri_arr[i].base_off +
					 bp->pri2cos[i];

				buf[j] = le64_to_cpu(*(tx_port_stats_ext + n));
			}
		}
	}
	if (bp->flags & BNXT_FLAG_PCIE_STATS) {
		__le64 *pcie_stats = (__le64 *)bp->hw_pcie_stats;

		for (i = 0; i < BNXT_NUM_PCIE_STATS; i++, j++) {
			buf[j] = le64_to_cpu(*(pcie_stats +
					       bnxt_pcie_stats_arr[i].offset));
		}
	}
}