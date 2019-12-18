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
struct rtnl_link_stats64 {int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_length_errors; scalar_t__ rx_errors; scalar_t__ rx_crc_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; } ;
struct ice_eth_stats {int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  tx_discards; int /*<<< orphan*/  rx_discards; int /*<<< orphan*/  tx_errors; } ;
struct ice_vsi {scalar_t__ type; int /*<<< orphan*/  state; struct ice_pf* back; struct ice_eth_stats eth_stats; struct rtnl_link_stats64 net_stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_discards; } ;
struct TYPE_4__ {TYPE_1__ eth; int /*<<< orphan*/  rx_len_errors; scalar_t__ illegal_bytes; scalar_t__ crc_errors; } ;
struct ice_pf {TYPE_2__ stats; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ ICE_VSI_PF ; 
 int /*<<< orphan*/  __ICE_CFG_BUSY ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  ice_update_eth_stats (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_update_vsi_ring_stats (struct ice_vsi*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ice_update_vsi_stats(struct ice_vsi *vsi)
{
	struct rtnl_link_stats64 *cur_ns = &vsi->net_stats;
	struct ice_eth_stats *cur_es = &vsi->eth_stats;
	struct ice_pf *pf = vsi->back;

	if (test_bit(__ICE_DOWN, vsi->state) ||
	    test_bit(__ICE_CFG_BUSY, pf->state))
		return;

	/* get stats as recorded by Tx/Rx rings */
	ice_update_vsi_ring_stats(vsi);

	/* get VSI stats as recorded by the hardware */
	ice_update_eth_stats(vsi);

	cur_ns->tx_errors = cur_es->tx_errors;
	cur_ns->rx_dropped = cur_es->rx_discards;
	cur_ns->tx_dropped = cur_es->tx_discards;
	cur_ns->multicast = cur_es->rx_multicast;

	/* update some more netdev stats if this is main VSI */
	if (vsi->type == ICE_VSI_PF) {
		cur_ns->rx_crc_errors = pf->stats.crc_errors;
		cur_ns->rx_errors = pf->stats.crc_errors +
				    pf->stats.illegal_bytes;
		cur_ns->rx_length_errors = pf->stats.rx_len_errors;
		/* record drops from the port level */
		cur_ns->rx_missed_errors = pf->stats.eth.rx_discards;
	}
}