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
typedef  int /*<<< orphan*/  u64 ;
struct dsaf_hw_stats {int /*<<< orphan*/  tx_pkts; int /*<<< orphan*/ * tx_pfc; int /*<<< orphan*/ * rx_pfc; int /*<<< orphan*/  stp_drop; int /*<<< orphan*/  vlan_drop; int /*<<< orphan*/  local_addr_false; int /*<<< orphan*/  rslt_drop; int /*<<< orphan*/  bp_drop; int /*<<< orphan*/  crc_false; int /*<<< orphan*/  sbm_drop; int /*<<< orphan*/  release_buf_num; int /*<<< orphan*/  rx_pause_frame; int /*<<< orphan*/  rx_pkt_id; int /*<<< orphan*/  rx_pkts; int /*<<< orphan*/  man_pkts; int /*<<< orphan*/  pad_drop; } ;
struct dsaf_device {int /*<<< orphan*/  dsaf_ver; struct dsaf_hw_stats* hw_stats; } ;

/* Variables and functions */
 int AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int DSAF_PRIO_NR ; 
 int DSAF_SERVICE_NW_NUM ; 

__attribute__((used)) static u64 *hns_dsaf_get_node_stats(struct dsaf_device *ddev, u64 *data,
				    int node_num)
{
	u64 *p = data;
	int i;
	struct dsaf_hw_stats *hw_stats = &ddev->hw_stats[node_num];
	bool is_ver1 = AE_IS_VER1(ddev->dsaf_ver);

	p[0] = hw_stats->pad_drop;
	p[1] = hw_stats->man_pkts;
	p[2] = hw_stats->rx_pkts;
	p[3] = hw_stats->rx_pkt_id;
	p[4] = hw_stats->rx_pause_frame;
	p[5] = hw_stats->release_buf_num;
	p[6] = hw_stats->sbm_drop;
	p[7] = hw_stats->crc_false;
	p[8] = hw_stats->bp_drop;
	p[9] = hw_stats->rslt_drop;
	p[10] = hw_stats->local_addr_false;
	p[11] = hw_stats->vlan_drop;
	p[12] = hw_stats->stp_drop;
	if (node_num < DSAF_SERVICE_NW_NUM && !is_ver1) {
		for (i = 0; i < DSAF_PRIO_NR; i++) {
			p[13 + i + 0 * DSAF_PRIO_NR] = hw_stats->rx_pfc[i];
			p[13 + i + 1 * DSAF_PRIO_NR] = hw_stats->tx_pfc[i];
		}
		p[29] = hw_stats->tx_pkts;
		return &p[30];
	}

	p[13] = hw_stats->tx_pkts;
	return &p[14];
}