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
struct r8152 {TYPE_1__* netdev; } ;
struct TYPE_2__ {int features; int mtu; } ;

/* Variables and functions */
 int ETH_FCS_LEN ; 
 int LINK_LIST_READY ; 
 int MCU_BORW_EN ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int MTPS_JUMBO ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NOW_IS_OOB ; 
 int /*<<< orphan*/  PLA_MTPS ; 
 int /*<<< orphan*/  PLA_OOB_CTRL ; 
 int /*<<< orphan*/  PLA_RCR ; 
 int /*<<< orphan*/  PLA_RMS ; 
 int /*<<< orphan*/  PLA_RXFIFO_CTRL0 ; 
 int /*<<< orphan*/  PLA_RXFIFO_CTRL1 ; 
 int /*<<< orphan*/  PLA_RXFIFO_CTRL2 ; 
 int /*<<< orphan*/  PLA_SFF_STS_7 ; 
 int /*<<< orphan*/  PLA_TCR0 ; 
 int /*<<< orphan*/  PLA_TXFIFO_CTRL ; 
 int RCR_ACPT_ALL ; 
 int RE_INIT_LL ; 
 int RXFIFO_THR1_NORMAL ; 
 int RXFIFO_THR2_NORMAL ; 
 int RXFIFO_THR3_NORMAL ; 
 int TCR0_AUTO_FIFO ; 
 int TXFIFO_THR_NORMAL2 ; 
 int VLAN_ETH_HLEN ; 
 int ocp_read_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_read_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8153_mac_clk_spd (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_teredo_off (struct r8152*) ; 
 int /*<<< orphan*/  rtl8152_nic_reset (struct r8152*) ; 
 int /*<<< orphan*/  rtl_reset_bmu (struct r8152*) ; 
 int /*<<< orphan*/  rtl_rx_vlan_en (struct r8152*,int) ; 
 int /*<<< orphan*/  rxdy_gated_en (struct r8152*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void r8153_first_init(struct r8152 *tp)
{
	u32 ocp_data;
	int i;

	r8153_mac_clk_spd(tp, false);
	rxdy_gated_en(tp, true);
	r8153_teredo_off(tp);

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rtl8152_nic_reset(tp);
	rtl_reset_bmu(tp);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	for (i = 0; i < 1000; i++) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		if (ocp_data & LINK_LIST_READY)
			break;
		usleep_range(1000, 2000);
	}

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	for (i = 0; i < 1000; i++) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		if (ocp_data & LINK_LIST_READY)
			break;
		usleep_range(1000, 2000);
	}

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	ocp_data = tp->netdev->mtu + VLAN_ETH_HLEN + ETH_FCS_LEN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, ocp_data);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_MTPS, MTPS_JUMBO);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TCR0);
	ocp_data |= TCR0_AUTO_FIFO;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_TCR0, ocp_data);

	rtl8152_nic_reset(tp);

	/* rx share fifo credit full threshold */
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_NORMAL);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1, RXFIFO_THR2_NORMAL);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2, RXFIFO_THR3_NORMAL);
	/* TX share fifo free credit full threshold */
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, TXFIFO_THR_NORMAL2);
}