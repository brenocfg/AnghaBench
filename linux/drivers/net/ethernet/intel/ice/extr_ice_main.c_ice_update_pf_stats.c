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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  tx_broadcast; int /*<<< orphan*/  tx_multicast; int /*<<< orphan*/  tx_unicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_discards; int /*<<< orphan*/  rx_broadcast; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_unicast; int /*<<< orphan*/  rx_bytes; } ;
struct ice_hw_port_stats {int /*<<< orphan*/  rx_jabber; int /*<<< orphan*/  rx_oversize; int /*<<< orphan*/  rx_fragments; int /*<<< orphan*/  rx_undersize; int /*<<< orphan*/  rx_len_errors; int /*<<< orphan*/  mac_remote_faults; int /*<<< orphan*/  mac_local_faults; int /*<<< orphan*/  illegal_bytes; int /*<<< orphan*/  crc_errors; int /*<<< orphan*/  link_xoff_tx; int /*<<< orphan*/  link_xon_tx; int /*<<< orphan*/  link_xoff_rx; int /*<<< orphan*/  link_xon_rx; int /*<<< orphan*/  tx_size_big; int /*<<< orphan*/  tx_size_1522; int /*<<< orphan*/  tx_size_1023; int /*<<< orphan*/  tx_size_511; int /*<<< orphan*/  tx_size_255; int /*<<< orphan*/  tx_size_127; int /*<<< orphan*/  tx_size_64; int /*<<< orphan*/  rx_size_big; int /*<<< orphan*/  rx_size_1522; int /*<<< orphan*/  rx_size_1023; int /*<<< orphan*/  rx_size_511; int /*<<< orphan*/  rx_size_255; int /*<<< orphan*/  rx_size_127; int /*<<< orphan*/  rx_size_64; int /*<<< orphan*/  tx_dropped_link_down; TYPE_2__ eth; } ;
struct ice_hw {TYPE_1__* port_info; } ;
struct ice_pf {int stat_prev_loaded; struct ice_hw_port_stats stats; struct ice_hw_port_stats stats_prev; struct ice_hw hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLPRT_BPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_BPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_CRCERRS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_GORCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_GOTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_ILLERRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_LXOFFRXC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_LXOFFTXC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_LXONRXC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_LXONTXC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_MLFC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_MPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_MPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_MRFC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC1023L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC127L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC1522L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC255L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC511L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC64L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PRC9522L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC1023L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC127L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC1522L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC255L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC511L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC64L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_PTC9522L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_RFC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_RJC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_RLEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_ROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_RUC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_TDOLD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_UPRCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLPRT_UPTCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRTRPB_RDPC ; 
 int /*<<< orphan*/  ice_stat_update32 (struct ice_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_stat_update40 (struct ice_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_update_dcb_stats (struct ice_pf*) ; 

void ice_update_pf_stats(struct ice_pf *pf)
{
	struct ice_hw_port_stats *prev_ps, *cur_ps;
	struct ice_hw *hw = &pf->hw;
	u8 port;

	port = hw->port_info->lport;
	prev_ps = &pf->stats_prev;
	cur_ps = &pf->stats;

	ice_stat_update40(hw, GLPRT_GORCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.rx_bytes,
			  &cur_ps->eth.rx_bytes);

	ice_stat_update40(hw, GLPRT_UPRCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.rx_unicast,
			  &cur_ps->eth.rx_unicast);

	ice_stat_update40(hw, GLPRT_MPRCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.rx_multicast,
			  &cur_ps->eth.rx_multicast);

	ice_stat_update40(hw, GLPRT_BPRCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.rx_broadcast,
			  &cur_ps->eth.rx_broadcast);

	ice_stat_update32(hw, PRTRPB_RDPC, pf->stat_prev_loaded,
			  &prev_ps->eth.rx_discards,
			  &cur_ps->eth.rx_discards);

	ice_stat_update40(hw, GLPRT_GOTCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.tx_bytes,
			  &cur_ps->eth.tx_bytes);

	ice_stat_update40(hw, GLPRT_UPTCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.tx_unicast,
			  &cur_ps->eth.tx_unicast);

	ice_stat_update40(hw, GLPRT_MPTCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.tx_multicast,
			  &cur_ps->eth.tx_multicast);

	ice_stat_update40(hw, GLPRT_BPTCL(port), pf->stat_prev_loaded,
			  &prev_ps->eth.tx_broadcast,
			  &cur_ps->eth.tx_broadcast);

	ice_stat_update32(hw, GLPRT_TDOLD(port), pf->stat_prev_loaded,
			  &prev_ps->tx_dropped_link_down,
			  &cur_ps->tx_dropped_link_down);

	ice_stat_update40(hw, GLPRT_PRC64L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_64, &cur_ps->rx_size_64);

	ice_stat_update40(hw, GLPRT_PRC127L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_127, &cur_ps->rx_size_127);

	ice_stat_update40(hw, GLPRT_PRC255L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_255, &cur_ps->rx_size_255);

	ice_stat_update40(hw, GLPRT_PRC511L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_511, &cur_ps->rx_size_511);

	ice_stat_update40(hw, GLPRT_PRC1023L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_1023, &cur_ps->rx_size_1023);

	ice_stat_update40(hw, GLPRT_PRC1522L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_1522, &cur_ps->rx_size_1522);

	ice_stat_update40(hw, GLPRT_PRC9522L(port), pf->stat_prev_loaded,
			  &prev_ps->rx_size_big, &cur_ps->rx_size_big);

	ice_stat_update40(hw, GLPRT_PTC64L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_64, &cur_ps->tx_size_64);

	ice_stat_update40(hw, GLPRT_PTC127L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_127, &cur_ps->tx_size_127);

	ice_stat_update40(hw, GLPRT_PTC255L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_255, &cur_ps->tx_size_255);

	ice_stat_update40(hw, GLPRT_PTC511L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_511, &cur_ps->tx_size_511);

	ice_stat_update40(hw, GLPRT_PTC1023L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_1023, &cur_ps->tx_size_1023);

	ice_stat_update40(hw, GLPRT_PTC1522L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_1522, &cur_ps->tx_size_1522);

	ice_stat_update40(hw, GLPRT_PTC9522L(port), pf->stat_prev_loaded,
			  &prev_ps->tx_size_big, &cur_ps->tx_size_big);

	ice_stat_update32(hw, GLPRT_LXONRXC(port), pf->stat_prev_loaded,
			  &prev_ps->link_xon_rx, &cur_ps->link_xon_rx);

	ice_stat_update32(hw, GLPRT_LXOFFRXC(port), pf->stat_prev_loaded,
			  &prev_ps->link_xoff_rx, &cur_ps->link_xoff_rx);

	ice_stat_update32(hw, GLPRT_LXONTXC(port), pf->stat_prev_loaded,
			  &prev_ps->link_xon_tx, &cur_ps->link_xon_tx);

	ice_stat_update32(hw, GLPRT_LXOFFTXC(port), pf->stat_prev_loaded,
			  &prev_ps->link_xoff_tx, &cur_ps->link_xoff_tx);

	ice_update_dcb_stats(pf);

	ice_stat_update32(hw, GLPRT_CRCERRS(port), pf->stat_prev_loaded,
			  &prev_ps->crc_errors, &cur_ps->crc_errors);

	ice_stat_update32(hw, GLPRT_ILLERRC(port), pf->stat_prev_loaded,
			  &prev_ps->illegal_bytes, &cur_ps->illegal_bytes);

	ice_stat_update32(hw, GLPRT_MLFC(port), pf->stat_prev_loaded,
			  &prev_ps->mac_local_faults,
			  &cur_ps->mac_local_faults);

	ice_stat_update32(hw, GLPRT_MRFC(port), pf->stat_prev_loaded,
			  &prev_ps->mac_remote_faults,
			  &cur_ps->mac_remote_faults);

	ice_stat_update32(hw, GLPRT_RLEC(port), pf->stat_prev_loaded,
			  &prev_ps->rx_len_errors, &cur_ps->rx_len_errors);

	ice_stat_update32(hw, GLPRT_RUC(port), pf->stat_prev_loaded,
			  &prev_ps->rx_undersize, &cur_ps->rx_undersize);

	ice_stat_update32(hw, GLPRT_RFC(port), pf->stat_prev_loaded,
			  &prev_ps->rx_fragments, &cur_ps->rx_fragments);

	ice_stat_update32(hw, GLPRT_ROC(port), pf->stat_prev_loaded,
			  &prev_ps->rx_oversize, &cur_ps->rx_oversize);

	ice_stat_update32(hw, GLPRT_RJC(port), pf->stat_prev_loaded,
			  &prev_ps->rx_jabber, &cur_ps->rx_jabber);

	pf->stat_prev_loaded = true;
}