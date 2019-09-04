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
struct TYPE_2__ {int /*<<< orphan*/  update; int /*<<< orphan*/  tx_mc_byte_cnt; int /*<<< orphan*/  tx_bc_byte_cnt; int /*<<< orphan*/  tx_trunc; int /*<<< orphan*/  tx_len_err; int /*<<< orphan*/  tx_trd_eop; int /*<<< orphan*/  tx_underrun; int /*<<< orphan*/  tx_abort_col; int /*<<< orphan*/  tx_late_col; int /*<<< orphan*/  tx_multi_col; int /*<<< orphan*/  tx_single_col; int /*<<< orphan*/  tx_sz_max; int /*<<< orphan*/  tx_sz_1518B; int /*<<< orphan*/  tx_sz_1023B; int /*<<< orphan*/  tx_sz_511B; int /*<<< orphan*/  tx_sz_255B; int /*<<< orphan*/  tx_sz_127B; int /*<<< orphan*/  tx_sz_64B; int /*<<< orphan*/  tx_byte_cnt; int /*<<< orphan*/  tx_defer; int /*<<< orphan*/  tx_ctrl; int /*<<< orphan*/  tx_exc_defer; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  tx_mcast; int /*<<< orphan*/  tx_bcast; int /*<<< orphan*/  tx_ok; int /*<<< orphan*/  rx_err_addr; int /*<<< orphan*/  rx_mc_byte_cnt; int /*<<< orphan*/  rx_bc_byte_cnt; int /*<<< orphan*/  rx_align_err; int /*<<< orphan*/  rx_ov_rrd; int /*<<< orphan*/  rx_ov_rxf; int /*<<< orphan*/  rx_ov_sz; int /*<<< orphan*/  rx_sz_max; int /*<<< orphan*/  rx_sz_1518B; int /*<<< orphan*/  rx_sz_1023B; int /*<<< orphan*/  rx_sz_511B; int /*<<< orphan*/  rx_sz_255B; int /*<<< orphan*/  rx_sz_127B; int /*<<< orphan*/  rx_sz_64B; int /*<<< orphan*/  rx_frag; int /*<<< orphan*/  rx_runt; int /*<<< orphan*/  rx_byte_cnt; int /*<<< orphan*/  rx_len_err; int /*<<< orphan*/  rx_fcs_err; int /*<<< orphan*/  rx_ctrl; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  rx_mcast; int /*<<< orphan*/  rx_bcast; int /*<<< orphan*/  rx_ok; } ;
struct alx_hw {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_MIB_RX_ALIGN_ERR ; 
 int /*<<< orphan*/  ALX_MIB_RX_BCAST ; 
 int /*<<< orphan*/  ALX_MIB_RX_BCCNT ; 
 int /*<<< orphan*/  ALX_MIB_RX_BYTE_CNT ; 
 int /*<<< orphan*/  ALX_MIB_RX_CTRL ; 
 int /*<<< orphan*/  ALX_MIB_RX_ERRADDR ; 
 int /*<<< orphan*/  ALX_MIB_RX_FCS_ERR ; 
 int /*<<< orphan*/  ALX_MIB_RX_FRAG ; 
 int /*<<< orphan*/  ALX_MIB_RX_LEN_ERR ; 
 int /*<<< orphan*/  ALX_MIB_RX_MCAST ; 
 int /*<<< orphan*/  ALX_MIB_RX_MCCNT ; 
 int /*<<< orphan*/  ALX_MIB_RX_OK ; 
 int /*<<< orphan*/  ALX_MIB_RX_OV_RRD ; 
 int /*<<< orphan*/  ALX_MIB_RX_OV_RXF ; 
 int /*<<< orphan*/  ALX_MIB_RX_OV_SZ ; 
 int /*<<< orphan*/  ALX_MIB_RX_PAUSE ; 
 int /*<<< orphan*/  ALX_MIB_RX_RUNT ; 
 int /*<<< orphan*/  ALX_MIB_RX_SZ_1023B ; 
 int /*<<< orphan*/  ALX_MIB_RX_SZ_127B ; 
 int /*<<< orphan*/  ALX_MIB_RX_SZ_1518B ; 
 int /*<<< orphan*/  ALX_MIB_RX_SZ_255B ; 
 int /*<<< orphan*/  ALX_MIB_RX_SZ_511B ; 
 int /*<<< orphan*/  ALX_MIB_RX_SZ_64B ; 
 int /*<<< orphan*/  ALX_MIB_RX_SZ_MAX ; 
 int /*<<< orphan*/  ALX_MIB_TX_ABORT_COL ; 
 int /*<<< orphan*/  ALX_MIB_TX_BCAST ; 
 int /*<<< orphan*/  ALX_MIB_TX_BCCNT ; 
 int /*<<< orphan*/  ALX_MIB_TX_BYTE_CNT ; 
 int /*<<< orphan*/  ALX_MIB_TX_CTRL ; 
 int /*<<< orphan*/  ALX_MIB_TX_DEFER ; 
 int /*<<< orphan*/  ALX_MIB_TX_EXC_DEFER ; 
 int /*<<< orphan*/  ALX_MIB_TX_LATE_COL ; 
 int /*<<< orphan*/  ALX_MIB_TX_LEN_ERR ; 
 int /*<<< orphan*/  ALX_MIB_TX_MCAST ; 
 int /*<<< orphan*/  ALX_MIB_TX_MCCNT ; 
 int /*<<< orphan*/  ALX_MIB_TX_MULTI_COL ; 
 int /*<<< orphan*/  ALX_MIB_TX_OK ; 
 int /*<<< orphan*/  ALX_MIB_TX_PAUSE ; 
 int /*<<< orphan*/  ALX_MIB_TX_SINGLE_COL ; 
 int /*<<< orphan*/  ALX_MIB_TX_SZ_1023B ; 
 int /*<<< orphan*/  ALX_MIB_TX_SZ_127B ; 
 int /*<<< orphan*/  ALX_MIB_TX_SZ_1518B ; 
 int /*<<< orphan*/  ALX_MIB_TX_SZ_255B ; 
 int /*<<< orphan*/  ALX_MIB_TX_SZ_511B ; 
 int /*<<< orphan*/  ALX_MIB_TX_SZ_64B ; 
 int /*<<< orphan*/  ALX_MIB_TX_SZ_MAX ; 
 int /*<<< orphan*/  ALX_MIB_TX_TRD_EOP ; 
 int /*<<< orphan*/  ALX_MIB_TX_TRUNC ; 
 int /*<<< orphan*/  ALX_MIB_TX_UNDERRUN ; 
 int /*<<< orphan*/  ALX_MIB_UPDATE ; 
 scalar_t__ alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 

void alx_update_hw_stats(struct alx_hw *hw)
{
	/* RX stats */
	hw->stats.rx_ok          += alx_read_mem32(hw, ALX_MIB_RX_OK);
	hw->stats.rx_bcast       += alx_read_mem32(hw, ALX_MIB_RX_BCAST);
	hw->stats.rx_mcast       += alx_read_mem32(hw, ALX_MIB_RX_MCAST);
	hw->stats.rx_pause       += alx_read_mem32(hw, ALX_MIB_RX_PAUSE);
	hw->stats.rx_ctrl        += alx_read_mem32(hw, ALX_MIB_RX_CTRL);
	hw->stats.rx_fcs_err     += alx_read_mem32(hw, ALX_MIB_RX_FCS_ERR);
	hw->stats.rx_len_err     += alx_read_mem32(hw, ALX_MIB_RX_LEN_ERR);
	hw->stats.rx_byte_cnt    += alx_read_mem32(hw, ALX_MIB_RX_BYTE_CNT);
	hw->stats.rx_runt        += alx_read_mem32(hw, ALX_MIB_RX_RUNT);
	hw->stats.rx_frag        += alx_read_mem32(hw, ALX_MIB_RX_FRAG);
	hw->stats.rx_sz_64B      += alx_read_mem32(hw, ALX_MIB_RX_SZ_64B);
	hw->stats.rx_sz_127B     += alx_read_mem32(hw, ALX_MIB_RX_SZ_127B);
	hw->stats.rx_sz_255B     += alx_read_mem32(hw, ALX_MIB_RX_SZ_255B);
	hw->stats.rx_sz_511B     += alx_read_mem32(hw, ALX_MIB_RX_SZ_511B);
	hw->stats.rx_sz_1023B    += alx_read_mem32(hw, ALX_MIB_RX_SZ_1023B);
	hw->stats.rx_sz_1518B    += alx_read_mem32(hw, ALX_MIB_RX_SZ_1518B);
	hw->stats.rx_sz_max      += alx_read_mem32(hw, ALX_MIB_RX_SZ_MAX);
	hw->stats.rx_ov_sz       += alx_read_mem32(hw, ALX_MIB_RX_OV_SZ);
	hw->stats.rx_ov_rxf      += alx_read_mem32(hw, ALX_MIB_RX_OV_RXF);
	hw->stats.rx_ov_rrd      += alx_read_mem32(hw, ALX_MIB_RX_OV_RRD);
	hw->stats.rx_align_err   += alx_read_mem32(hw, ALX_MIB_RX_ALIGN_ERR);
	hw->stats.rx_bc_byte_cnt += alx_read_mem32(hw, ALX_MIB_RX_BCCNT);
	hw->stats.rx_mc_byte_cnt += alx_read_mem32(hw, ALX_MIB_RX_MCCNT);
	hw->stats.rx_err_addr    += alx_read_mem32(hw, ALX_MIB_RX_ERRADDR);

	/* TX stats */
	hw->stats.tx_ok          += alx_read_mem32(hw, ALX_MIB_TX_OK);
	hw->stats.tx_bcast       += alx_read_mem32(hw, ALX_MIB_TX_BCAST);
	hw->stats.tx_mcast       += alx_read_mem32(hw, ALX_MIB_TX_MCAST);
	hw->stats.tx_pause       += alx_read_mem32(hw, ALX_MIB_TX_PAUSE);
	hw->stats.tx_exc_defer   += alx_read_mem32(hw, ALX_MIB_TX_EXC_DEFER);
	hw->stats.tx_ctrl        += alx_read_mem32(hw, ALX_MIB_TX_CTRL);
	hw->stats.tx_defer       += alx_read_mem32(hw, ALX_MIB_TX_DEFER);
	hw->stats.tx_byte_cnt    += alx_read_mem32(hw, ALX_MIB_TX_BYTE_CNT);
	hw->stats.tx_sz_64B      += alx_read_mem32(hw, ALX_MIB_TX_SZ_64B);
	hw->stats.tx_sz_127B     += alx_read_mem32(hw, ALX_MIB_TX_SZ_127B);
	hw->stats.tx_sz_255B     += alx_read_mem32(hw, ALX_MIB_TX_SZ_255B);
	hw->stats.tx_sz_511B     += alx_read_mem32(hw, ALX_MIB_TX_SZ_511B);
	hw->stats.tx_sz_1023B    += alx_read_mem32(hw, ALX_MIB_TX_SZ_1023B);
	hw->stats.tx_sz_1518B    += alx_read_mem32(hw, ALX_MIB_TX_SZ_1518B);
	hw->stats.tx_sz_max      += alx_read_mem32(hw, ALX_MIB_TX_SZ_MAX);
	hw->stats.tx_single_col  += alx_read_mem32(hw, ALX_MIB_TX_SINGLE_COL);
	hw->stats.tx_multi_col   += alx_read_mem32(hw, ALX_MIB_TX_MULTI_COL);
	hw->stats.tx_late_col    += alx_read_mem32(hw, ALX_MIB_TX_LATE_COL);
	hw->stats.tx_abort_col   += alx_read_mem32(hw, ALX_MIB_TX_ABORT_COL);
	hw->stats.tx_underrun    += alx_read_mem32(hw, ALX_MIB_TX_UNDERRUN);
	hw->stats.tx_trd_eop     += alx_read_mem32(hw, ALX_MIB_TX_TRD_EOP);
	hw->stats.tx_len_err     += alx_read_mem32(hw, ALX_MIB_TX_LEN_ERR);
	hw->stats.tx_trunc       += alx_read_mem32(hw, ALX_MIB_TX_TRUNC);
	hw->stats.tx_bc_byte_cnt += alx_read_mem32(hw, ALX_MIB_TX_BCCNT);
	hw->stats.tx_mc_byte_cnt += alx_read_mem32(hw, ALX_MIB_TX_MCCNT);

	hw->stats.update         += alx_read_mem32(hw, ALX_MIB_UPDATE);
}