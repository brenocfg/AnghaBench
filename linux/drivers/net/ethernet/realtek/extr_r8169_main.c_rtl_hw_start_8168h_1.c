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
typedef  int u16 ;
struct rtl8169_private {int dummy; } ;
struct ephy_info {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DLLPR ; 
 int /*<<< orphan*/  ERIAR_MASK_0011 ; 
 int /*<<< orphan*/  ERIAR_MASK_1111 ; 
 int /*<<< orphan*/  MISC ; 
 int /*<<< orphan*/  MISC_1 ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_READRQ_4096B ; 
 int PFM_D3COLD_EN ; 
 int PFM_EN ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int RXDV_GATED_EN ; 
 int TX_10M_PS_EN ; 
 int /*<<< orphan*/  r8168_mac_ocp_modify (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  r8168_mac_ocp_write (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl8168_config_eee_mac (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168g_set_pause_thresholds (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_ephy_init (struct rtl8169_private*,struct ephy_info const*) ; 
 int /*<<< orphan*/  rtl_eri_clear_bits (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_eri_set_bits (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_hw_aspm_clkreq_enable (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_pcie_state_l2l3_disable (struct rtl8169_private*) ; 
 int rtl_readphy (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_reset_packet_filter (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_def_aspm_entry_latency (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_fifo_size (struct rtl8169_private*,int,int,int,int) ; 
 int /*<<< orphan*/  rtl_tx_performance_tweak (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl_hw_start_8168h_1(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8168h_1[] = {
		{ 0x1e, 0x0800,	0x0001 },
		{ 0x1d, 0x0000,	0x0800 },
		{ 0x05, 0xffff,	0x2089 },
		{ 0x06, 0xffff,	0x5881 },
		{ 0x04, 0xffff,	0x854a },
		{ 0x01, 0xffff,	0x068b }
	};
	int rg_saw_cnt;

	/* disable aspm and clock request before access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8168h_1);

	rtl_set_fifo_size(tp, 0x08, 0x10, 0x02, 0x06);
	rtl8168g_set_pause_thresholds(tp, 0x38, 0x48);

	rtl_set_def_aspm_entry_latency(tp);

	rtl_tx_performance_tweak(tp, PCI_EXP_DEVCTL_READRQ_4096B);

	rtl_reset_packet_filter(tp);

	rtl_eri_set_bits(tp, 0xdc, ERIAR_MASK_1111, BIT(4));

	rtl_eri_set_bits(tp, 0xd4, ERIAR_MASK_1111, 0x1f00);

	rtl_eri_write(tp, 0x5f0, ERIAR_MASK_0011, 0x4f87);

	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~RXDV_GATED_EN);

	rtl_eri_write(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_write(tp, 0xb8, ERIAR_MASK_0011, 0x0000);

	rtl8168_config_eee_mac(tp);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~PFM_EN);
	RTL_W8(tp, MISC_1, RTL_R8(tp, MISC_1) & ~PFM_D3COLD_EN);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~TX_10M_PS_EN);

	rtl_eri_clear_bits(tp, 0x1b0, ERIAR_MASK_0011, BIT(12));

	rtl_pcie_state_l2l3_disable(tp);

	rtl_writephy(tp, 0x1f, 0x0c42);
	rg_saw_cnt = (rtl_readphy(tp, 0x13) & 0x3fff);
	rtl_writephy(tp, 0x1f, 0x0000);
	if (rg_saw_cnt > 0) {
		u16 sw_cnt_1ms_ini;

		sw_cnt_1ms_ini = 16000000/rg_saw_cnt;
		sw_cnt_1ms_ini &= 0x0fff;
		r8168_mac_ocp_modify(tp, 0xd412, 0x0fff, sw_cnt_1ms_ini);
	}

	r8168_mac_ocp_modify(tp, 0xe056, 0x00f0, 0x0070);
	r8168_mac_ocp_modify(tp, 0xe052, 0x6000, 0x8008);
	r8168_mac_ocp_modify(tp, 0xe0d6, 0x01ff, 0x017f);
	r8168_mac_ocp_modify(tp, 0xd420, 0x0fff, 0x047f);

	r8168_mac_ocp_write(tp, 0xe63e, 0x0001);
	r8168_mac_ocp_write(tp, 0xe63e, 0x0000);
	r8168_mac_ocp_write(tp, 0xc094, 0x0000);
	r8168_mac_ocp_write(tp, 0xc09e, 0x0000);

	rtl_hw_aspm_clkreq_enable(tp, true);
}