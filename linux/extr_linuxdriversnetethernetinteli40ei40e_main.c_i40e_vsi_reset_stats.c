#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtnl_link_stats64 {int dummy; } ;
struct i40e_vsi {int num_queue_pairs; int stat_offsets_loaded; TYPE_2__** tx_rings; TYPE_1__** rx_rings; struct rtnl_link_stats64 eth_stats_offsets; struct rtnl_link_stats64 eth_stats; struct rtnl_link_stats64 net_stats_offsets; } ;
struct TYPE_4__ {struct rtnl_link_stats64 tx_stats; struct rtnl_link_stats64 stats; } ;
struct TYPE_3__ {struct rtnl_link_stats64 rx_stats; struct rtnl_link_stats64 stats; } ;

/* Variables and functions */
 struct rtnl_link_stats64* i40e_get_vsi_stats_struct (struct i40e_vsi*) ; 
 int /*<<< orphan*/  memset (struct rtnl_link_stats64*,int /*<<< orphan*/ ,int) ; 

void i40e_vsi_reset_stats(struct i40e_vsi *vsi)
{
	struct rtnl_link_stats64 *ns;
	int i;

	if (!vsi)
		return;

	ns = i40e_get_vsi_stats_struct(vsi);
	memset(ns, 0, sizeof(*ns));
	memset(&vsi->net_stats_offsets, 0, sizeof(vsi->net_stats_offsets));
	memset(&vsi->eth_stats, 0, sizeof(vsi->eth_stats));
	memset(&vsi->eth_stats_offsets, 0, sizeof(vsi->eth_stats_offsets));
	if (vsi->rx_rings && vsi->rx_rings[0]) {
		for (i = 0; i < vsi->num_queue_pairs; i++) {
			memset(&vsi->rx_rings[i]->stats, 0,
			       sizeof(vsi->rx_rings[i]->stats));
			memset(&vsi->rx_rings[i]->rx_stats, 0,
			       sizeof(vsi->rx_rings[i]->rx_stats));
			memset(&vsi->tx_rings[i]->stats, 0,
			       sizeof(vsi->tx_rings[i]->stats));
			memset(&vsi->tx_rings[i]->tx_stats, 0,
			       sizeof(vsi->tx_rings[i]->tx_stats));
		}
	}
	vsi->stat_offsets_loaded = false;
}