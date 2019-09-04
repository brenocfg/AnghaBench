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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  tx_broadcast; int /*<<< orphan*/  tx_multicast; int /*<<< orphan*/  tx_unicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_broadcast; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_unicast; int /*<<< orphan*/  rx_bytes; } ;
struct ice_hw_port_stats {int /*<<< orphan*/  rx_jabber; int /*<<< orphan*/  rx_oversize; int /*<<< orphan*/  rx_fragments; int /*<<< orphan*/  rx_undersize; int /*<<< orphan*/  rx_len_errors; int /*<<< orphan*/  mac_remote_faults; int /*<<< orphan*/  mac_local_faults; int /*<<< orphan*/  illegal_bytes; int /*<<< orphan*/  crc_errors; int /*<<< orphan*/  link_xoff_tx; int /*<<< orphan*/  link_xon_tx; int /*<<< orphan*/  link_xoff_rx; int /*<<< orphan*/  link_xon_rx; int /*<<< orphan*/  tx_size_big; int /*<<< orphan*/  tx_size_1522; int /*<<< orphan*/  tx_size_1023; int /*<<< orphan*/  tx_size_511; int /*<<< orphan*/  tx_size_255; int /*<<< orphan*/  tx_size_127; int /*<<< orphan*/  tx_size_64; int /*<<< orphan*/  rx_size_big; int /*<<< orphan*/  rx_size_1522; int /*<<< orphan*/  rx_size_1023; int /*<<< orphan*/  rx_size_511; int /*<<< orphan*/  rx_size_255; int /*<<< orphan*/  rx_size_127; int /*<<< orphan*/  rx_size_64; int /*<<< orphan*/  tx_dropped_link_down; TYPE_1__ eth; } ;
struct ice_hw {int /*<<< orphan*/  pf_id; } ;
struct ice_pf {int stat_prev_loaded; struct ice_hw_port_stats stats; struct ice_hw_port_stats stats_prev; struct ice_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLPRT_BPRCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_BPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_BPTCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_BPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_CRCERRS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_GORCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_GORCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_GOTCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_GOTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_ILLERRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_LXOFFRXC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_LXOFFTXC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_LXONRXC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_LXONTXC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_MLFC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_MPRCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_MPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_MPTCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_MPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_MRFC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC1023H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC1023L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC127H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC127L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC1522H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC1522L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC255H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC255L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC511H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC511L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC64H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC64L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC9522H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC9522L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC1023H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC1023L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC127H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC127L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC1522H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC1522L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC255H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC255L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC511H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC511L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC64H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC64L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC9522H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC9522L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_RFC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_RJC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_RLEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_ROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_RUC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_TDOLD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_UPRCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_UPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_UPTCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_UPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_stat_update32 (struct ice_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_stat_update40 (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ice_update_pf_stats(struct ice_pf *pf)
{
	struct ice_hw_port_stats *prev_ps, *cur_ps;
	struct ice_hw *hw = &pf->hw;
	u8 pf_id;

	prev_ps = &pf->stats_prev;
	cur_ps = &pf->stats;
	pf_id = hw->pf_id;

	ice_stat_update40(hw, GLPRT_GORCH(pf_id), GLPRT_GORCL(pf_id),
			  pf->stat_prev_loaded, &prev_ps->eth.rx_bytes,
			  &cur_ps->eth.rx_bytes);

	ice_stat_update40(hw, GLPRT_UPRCH(pf_id), GLPRT_UPRCL(pf_id),
			  pf->stat_prev_loaded, &prev_ps->eth.rx_unicast,
			  &cur_ps->eth.rx_unicast);

	ice_stat_update40(hw, GLPRT_MPRCH(pf_id), GLPRT_MPRCL(pf_id),
			  pf->stat_prev_loaded, &prev_ps->eth.rx_multicast,
			  &cur_ps->eth.rx_multicast);

	ice_stat_update40(hw, GLPRT_BPRCH(pf_id), GLPRT_BPRCL(pf_id),
			  pf->stat_prev_loaded, &prev_ps->eth.rx_broadcast,
			  &cur_ps->eth.rx_broadcast);

	ice_stat_update40(hw, GLPRT_GOTCH(pf_id), GLPRT_GOTCL(pf_id),
			  pf->stat_prev_loaded, &prev_ps->eth.tx_bytes,
			  &cur_ps->eth.tx_bytes);

	ice_stat_update40(hw, GLPRT_UPTCH(pf_id), GLPRT_UPTCL(pf_id),
			  pf->stat_prev_loaded, &prev_ps->eth.tx_unicast,
			  &cur_ps->eth.tx_unicast);

	ice_stat_update40(hw, GLPRT_MPTCH(pf_id), GLPRT_MPTCL(pf_id),
			  pf->stat_prev_loaded, &prev_ps->eth.tx_multicast,
			  &cur_ps->eth.tx_multicast);

	ice_stat_update40(hw, GLPRT_BPTCH(pf_id), GLPRT_BPTCL(pf_id),
			  pf->stat_prev_loaded, &prev_ps->eth.tx_broadcast,
			  &cur_ps->eth.tx_broadcast);

	ice_stat_update32(hw, GLPRT_TDOLD(pf_id), pf->stat_prev_loaded,
			  &prev_ps->tx_dropped_link_down,
			  &cur_ps->tx_dropped_link_down);

	ice_stat_update40(hw, GLPRT_PRC64H(pf_id), GLPRT_PRC64L(pf_id),
			  pf->stat_prev_loaded, &prev_ps->rx_size_64,
			  &cur_ps->rx_size_64);

	ice_stat_update40(hw, GLPRT_PRC127H(pf_id), GLPRT_PRC127L(pf_id),
			  pf->stat_prev_loaded, &prev_ps->rx_size_127,
			  &cur_ps->rx_size_127);

	ice_stat_update40(hw, GLPRT_PRC255H(pf_id), GLPRT_PRC255L(pf_id),
			  pf->stat_prev_loaded, &prev_ps->rx_size_255,
			  &cur_ps->rx_size_255);

	ice_stat_update40(hw, GLPRT_PRC511H(pf_id), GLPRT_PRC511L(pf_id),
			  pf->stat_prev_loaded, &prev_ps->rx_size_511,
			  &cur_ps->rx_size_511);

	ice_stat_update40(hw, GLPRT_PRC1023H(pf_id),
			  GLPRT_PRC1023L(pf_id), pf->stat_prev_loaded,
			  &prev_ps->rx_size_1023, &cur_ps->rx_size_1023);

	ice_stat_update40(hw, GLPRT_PRC1522H(pf_id),
			  GLPRT_PRC1522L(pf_id), pf->stat_prev_loaded,
			  &prev_ps->rx_size_1522, &cur_ps->rx_size_1522);

	ice_stat_update40(hw, GLPRT_PRC9522H(pf_id),
			  GLPRT_PRC9522L(pf_id), pf->stat_prev_loaded,
			  &prev_ps->rx_size_big, &cur_ps->rx_size_big);

	ice_stat_update40(hw, GLPRT_PTC64H(pf_id), GLPRT_PTC64L(pf_id),
			  pf->stat_prev_loaded, &prev_ps->tx_size_64,
			  &cur_ps->tx_size_64);

	ice_stat_update40(hw, GLPRT_PTC127H(pf_id), GLPRT_PTC127L(pf_id),
			  pf->stat_prev_loaded, &prev_ps->tx_size_127,
			  &cur_ps->tx_size_127);

	ice_stat_update40(hw, GLPRT_PTC255H(pf_id), GLPRT_PTC255L(pf_id),
			  pf->stat_prev_loaded, &prev_ps->tx_size_255,
			  &cur_ps->tx_size_255);

	ice_stat_update40(hw, GLPRT_PTC511H(pf_id), GLPRT_PTC511L(pf_id),
			  pf->stat_prev_loaded, &prev_ps->tx_size_511,
			  &cur_ps->tx_size_511);

	ice_stat_update40(hw, GLPRT_PTC1023H(pf_id),
			  GLPRT_PTC1023L(pf_id), pf->stat_prev_loaded,
			  &prev_ps->tx_size_1023, &cur_ps->tx_size_1023);

	ice_stat_update40(hw, GLPRT_PTC1522H(pf_id),
			  GLPRT_PTC1522L(pf_id), pf->stat_prev_loaded,
			  &prev_ps->tx_size_1522, &cur_ps->tx_size_1522);

	ice_stat_update40(hw, GLPRT_PTC9522H(pf_id),
			  GLPRT_PTC9522L(pf_id), pf->stat_prev_loaded,
			  &prev_ps->tx_size_big, &cur_ps->tx_size_big);

	ice_stat_update32(hw, GLPRT_LXONRXC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->link_xon_rx, &cur_ps->link_xon_rx);

	ice_stat_update32(hw, GLPRT_LXOFFRXC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->link_xoff_rx, &cur_ps->link_xoff_rx);

	ice_stat_update32(hw, GLPRT_LXONTXC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->link_xon_tx, &cur_ps->link_xon_tx);

	ice_stat_update32(hw, GLPRT_LXOFFTXC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->link_xoff_tx, &cur_ps->link_xoff_tx);

	ice_stat_update32(hw, GLPRT_CRCERRS(pf_id), pf->stat_prev_loaded,
			  &prev_ps->crc_errors, &cur_ps->crc_errors);

	ice_stat_update32(hw, GLPRT_ILLERRC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->illegal_bytes, &cur_ps->illegal_bytes);

	ice_stat_update32(hw, GLPRT_MLFC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->mac_local_faults,
			  &cur_ps->mac_local_faults);

	ice_stat_update32(hw, GLPRT_MRFC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->mac_remote_faults,
			  &cur_ps->mac_remote_faults);

	ice_stat_update32(hw, GLPRT_RLEC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->rx_len_errors, &cur_ps->rx_len_errors);

	ice_stat_update32(hw, GLPRT_RUC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->rx_undersize, &cur_ps->rx_undersize);

	ice_stat_update32(hw, GLPRT_RFC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->rx_fragments, &cur_ps->rx_fragments);

	ice_stat_update32(hw, GLPRT_ROC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->rx_oversize, &cur_ps->rx_oversize);

	ice_stat_update32(hw, GLPRT_RJC(pf_id), pf->stat_prev_loaded,
			  &prev_ps->rx_jabber, &cur_ps->rx_jabber);

	pf->stat_prev_loaded = true;
}