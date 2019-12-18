#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ice_eth_stats {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_broadcast; int /*<<< orphan*/  tx_multicast; int /*<<< orphan*/  tx_unicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_discards; int /*<<< orphan*/  rx_broadcast; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_unicast; int /*<<< orphan*/  rx_bytes; } ;
struct ice_vsi {int stat_offsets_loaded; struct ice_eth_stats eth_stats; struct ice_eth_stats eth_stats_prev; int /*<<< orphan*/  vsi_num; TYPE_1__* back; } ;
struct ice_hw {int dummy; } ;
struct TYPE_2__ {struct ice_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLV_BPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLV_BPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLV_GORCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLV_GOTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLV_MPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLV_MPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLV_RDPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLV_TEPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLV_UPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLV_UPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_stat_update32 (struct ice_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_stat_update40 (struct ice_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ice_update_eth_stats(struct ice_vsi *vsi)
{
	struct ice_eth_stats *prev_es, *cur_es;
	struct ice_hw *hw = &vsi->back->hw;
	u16 vsi_num = vsi->vsi_num;    /* HW absolute index of a VSI */

	prev_es = &vsi->eth_stats_prev;
	cur_es = &vsi->eth_stats;

	ice_stat_update40(hw, GLV_GORCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->rx_bytes, &cur_es->rx_bytes);

	ice_stat_update40(hw, GLV_UPRCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->rx_unicast, &cur_es->rx_unicast);

	ice_stat_update40(hw, GLV_MPRCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->rx_multicast, &cur_es->rx_multicast);

	ice_stat_update40(hw, GLV_BPRCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->rx_broadcast, &cur_es->rx_broadcast);

	ice_stat_update32(hw, GLV_RDPC(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->rx_discards, &cur_es->rx_discards);

	ice_stat_update40(hw, GLV_GOTCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->tx_bytes, &cur_es->tx_bytes);

	ice_stat_update40(hw, GLV_UPTCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->tx_unicast, &cur_es->tx_unicast);

	ice_stat_update40(hw, GLV_MPTCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->tx_multicast, &cur_es->tx_multicast);

	ice_stat_update40(hw, GLV_BPTCL(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->tx_broadcast, &cur_es->tx_broadcast);

	ice_stat_update32(hw, GLV_TEPC(vsi_num), vsi->stat_offsets_loaded,
			  &prev_es->tx_errors, &cur_es->tx_errors);

	vsi->stat_offsets_loaded = true;
}