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
typedef  int u32 ;
struct port_stats {void* rx_trunc3; void* rx_trunc2; void* rx_trunc1; void* rx_trunc0; void* rx_ovflow3; void* rx_ovflow2; void* rx_ovflow1; void* rx_ovflow0; void* rx_pause; void* rx_mcast_frames; void* rx_frames_64; void* rx_ppp7; void* rx_ppp6; void* rx_ppp5; void* rx_ppp4; void* rx_ppp3; void* rx_ppp2; void* rx_ppp1; void* rx_ppp0; void* rx_frames_1519_max; void* rx_frames_1024_1518; void* rx_frames_512_1023; void* rx_frames_256_511; void* rx_frames_128_255; void* rx_frames_65_127; void* rx_runt; void* rx_symbol_err; void* rx_len_err; void* rx_fcs_err; void* rx_jabber; void* rx_too_long; void* rx_ucast_frames; void* rx_bcast_frames; void* rx_frames; void* rx_octets; void* tx_pause; void* tx_mcast_frames; void* tx_frames_64; void* tx_ppp7; void* tx_ppp6; void* tx_ppp5; void* tx_ppp4; void* tx_ppp3; void* tx_ppp2; void* tx_ppp1; void* tx_ppp0; void* tx_drop; void* tx_frames_1519_max; void* tx_frames_1024_1518; void* tx_frames_512_1023; void* tx_frames_256_511; void* tx_frames_128_255; void* tx_frames_65_127; void* tx_error_frames; void* tx_ucast_frames; void* tx_bcast_frames; void* tx_frames; void* tx_octets; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T5 ; 
 int COUNTPAUSEMCRX_F ; 
 int COUNTPAUSEMCTX_F ; 
 int COUNTPAUSESTATRX_F ; 
 int COUNTPAUSESTATTX_F ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_1024B_1518B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_128B_255B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_1519B_MAX_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_256B_511B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_512B_1023B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_64B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_65B_127B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_BCAST_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_BYTES_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_CRC_ERROR_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_FRAMES_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_LEN_ERROR_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_LESS_64B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_MCAST_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_MTU_CRC_ERROR_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_MTU_ERROR_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_PAUSE_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_PPP0_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_PPP1_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_PPP2_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_PPP3_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_PPP4_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_PPP5_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_PPP6_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_PPP7_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_SYM_ERROR_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_RX_PORT_UCAST_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_1024B_1518B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_128B_255B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_1519B_MAX_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_256B_511B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_512B_1023B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_64B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_65B_127B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_BCAST_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_BYTES_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_DROP_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_ERROR_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_FRAMES_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_MCAST_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_PAUSE_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_PPP0_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_PPP1_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_PPP2_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_PPP3_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_PPP4_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_PPP5_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_PPP6_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_PPP7_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_TX_PORT_UCAST_L ; 
 int /*<<< orphan*/  MPS_STAT_CTL_A ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_0_MAC_DROP_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_0_MAC_TRUNC_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_1_MAC_DROP_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_1_MAC_TRUNC_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_2_MAC_DROP_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_2_MAC_TRUNC_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_3_MAC_DROP_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_3_MAC_TRUNC_FRAME_L ; 
 int /*<<< orphan*/  PORT_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T5_PORT_REG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int t4_get_mps_bg_map (struct adapter*,int) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 void* t4_read_reg64 (struct adapter*,int /*<<< orphan*/ ) ; 

void t4_get_port_stats(struct adapter *adap, int idx, struct port_stats *p)
{
	u32 bgmap = t4_get_mps_bg_map(adap, idx);
	u32 stat_ctl = t4_read_reg(adap, MPS_STAT_CTL_A);

#define GET_STAT(name) \
	t4_read_reg64(adap, \
	(is_t4(adap->params.chip) ? PORT_REG(idx, MPS_PORT_STAT_##name##_L) : \
	T5_PORT_REG(idx, MPS_PORT_STAT_##name##_L)))
#define GET_STAT_COM(name) t4_read_reg64(adap, MPS_STAT_##name##_L)

	p->tx_octets           = GET_STAT(TX_PORT_BYTES);
	p->tx_frames           = GET_STAT(TX_PORT_FRAMES);
	p->tx_bcast_frames     = GET_STAT(TX_PORT_BCAST);
	p->tx_mcast_frames     = GET_STAT(TX_PORT_MCAST);
	p->tx_ucast_frames     = GET_STAT(TX_PORT_UCAST);
	p->tx_error_frames     = GET_STAT(TX_PORT_ERROR);
	p->tx_frames_64        = GET_STAT(TX_PORT_64B);
	p->tx_frames_65_127    = GET_STAT(TX_PORT_65B_127B);
	p->tx_frames_128_255   = GET_STAT(TX_PORT_128B_255B);
	p->tx_frames_256_511   = GET_STAT(TX_PORT_256B_511B);
	p->tx_frames_512_1023  = GET_STAT(TX_PORT_512B_1023B);
	p->tx_frames_1024_1518 = GET_STAT(TX_PORT_1024B_1518B);
	p->tx_frames_1519_max  = GET_STAT(TX_PORT_1519B_MAX);
	p->tx_drop             = GET_STAT(TX_PORT_DROP);
	p->tx_pause            = GET_STAT(TX_PORT_PAUSE);
	p->tx_ppp0             = GET_STAT(TX_PORT_PPP0);
	p->tx_ppp1             = GET_STAT(TX_PORT_PPP1);
	p->tx_ppp2             = GET_STAT(TX_PORT_PPP2);
	p->tx_ppp3             = GET_STAT(TX_PORT_PPP3);
	p->tx_ppp4             = GET_STAT(TX_PORT_PPP4);
	p->tx_ppp5             = GET_STAT(TX_PORT_PPP5);
	p->tx_ppp6             = GET_STAT(TX_PORT_PPP6);
	p->tx_ppp7             = GET_STAT(TX_PORT_PPP7);

	if (CHELSIO_CHIP_VERSION(adap->params.chip) >= CHELSIO_T5) {
		if (stat_ctl & COUNTPAUSESTATTX_F)
			p->tx_frames_64 -= p->tx_pause;
		if (stat_ctl & COUNTPAUSEMCTX_F)
			p->tx_mcast_frames -= p->tx_pause;
	}
	p->rx_octets           = GET_STAT(RX_PORT_BYTES);
	p->rx_frames           = GET_STAT(RX_PORT_FRAMES);
	p->rx_bcast_frames     = GET_STAT(RX_PORT_BCAST);
	p->rx_mcast_frames     = GET_STAT(RX_PORT_MCAST);
	p->rx_ucast_frames     = GET_STAT(RX_PORT_UCAST);
	p->rx_too_long         = GET_STAT(RX_PORT_MTU_ERROR);
	p->rx_jabber           = GET_STAT(RX_PORT_MTU_CRC_ERROR);
	p->rx_fcs_err          = GET_STAT(RX_PORT_CRC_ERROR);
	p->rx_len_err          = GET_STAT(RX_PORT_LEN_ERROR);
	p->rx_symbol_err       = GET_STAT(RX_PORT_SYM_ERROR);
	p->rx_runt             = GET_STAT(RX_PORT_LESS_64B);
	p->rx_frames_64        = GET_STAT(RX_PORT_64B);
	p->rx_frames_65_127    = GET_STAT(RX_PORT_65B_127B);
	p->rx_frames_128_255   = GET_STAT(RX_PORT_128B_255B);
	p->rx_frames_256_511   = GET_STAT(RX_PORT_256B_511B);
	p->rx_frames_512_1023  = GET_STAT(RX_PORT_512B_1023B);
	p->rx_frames_1024_1518 = GET_STAT(RX_PORT_1024B_1518B);
	p->rx_frames_1519_max  = GET_STAT(RX_PORT_1519B_MAX);
	p->rx_pause            = GET_STAT(RX_PORT_PAUSE);
	p->rx_ppp0             = GET_STAT(RX_PORT_PPP0);
	p->rx_ppp1             = GET_STAT(RX_PORT_PPP1);
	p->rx_ppp2             = GET_STAT(RX_PORT_PPP2);
	p->rx_ppp3             = GET_STAT(RX_PORT_PPP3);
	p->rx_ppp4             = GET_STAT(RX_PORT_PPP4);
	p->rx_ppp5             = GET_STAT(RX_PORT_PPP5);
	p->rx_ppp6             = GET_STAT(RX_PORT_PPP6);
	p->rx_ppp7             = GET_STAT(RX_PORT_PPP7);

	if (CHELSIO_CHIP_VERSION(adap->params.chip) >= CHELSIO_T5) {
		if (stat_ctl & COUNTPAUSESTATRX_F)
			p->rx_frames_64 -= p->rx_pause;
		if (stat_ctl & COUNTPAUSEMCRX_F)
			p->rx_mcast_frames -= p->rx_pause;
	}

	p->rx_ovflow0 = (bgmap & 1) ? GET_STAT_COM(RX_BG_0_MAC_DROP_FRAME) : 0;
	p->rx_ovflow1 = (bgmap & 2) ? GET_STAT_COM(RX_BG_1_MAC_DROP_FRAME) : 0;
	p->rx_ovflow2 = (bgmap & 4) ? GET_STAT_COM(RX_BG_2_MAC_DROP_FRAME) : 0;
	p->rx_ovflow3 = (bgmap & 8) ? GET_STAT_COM(RX_BG_3_MAC_DROP_FRAME) : 0;
	p->rx_trunc0 = (bgmap & 1) ? GET_STAT_COM(RX_BG_0_MAC_TRUNC_FRAME) : 0;
	p->rx_trunc1 = (bgmap & 2) ? GET_STAT_COM(RX_BG_1_MAC_TRUNC_FRAME) : 0;
	p->rx_trunc2 = (bgmap & 4) ? GET_STAT_COM(RX_BG_2_MAC_TRUNC_FRAME) : 0;
	p->rx_trunc3 = (bgmap & 8) ? GET_STAT_COM(RX_BG_3_MAC_TRUNC_FRAME) : 0;

#undef GET_STAT
#undef GET_STAT_COM
}