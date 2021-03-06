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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLLPR ; 
 int /*<<< orphan*/  ERIAR_MASK_0001 ; 
 int /*<<< orphan*/  ERIAR_MASK_0011 ; 
 int /*<<< orphan*/  ERIAR_MASK_1111 ; 
 int /*<<< orphan*/  MISC ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_READRQ_4096B ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int RXDV_GATED_EN ; 
 int TX_10M_PS_EN ; 
 int /*<<< orphan*/  rtl8168_config_eee_mac (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168ep_stop_cmac (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168g_set_pause_thresholds (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_eri_set_bits (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_pcie_state_l2l3_disable (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_reset_packet_filter (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_def_aspm_entry_latency (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_fifo_size (struct rtl8169_private*,int,int,int,int) ; 
 int /*<<< orphan*/  rtl_tx_performance_tweak (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_w0w1_eri (struct rtl8169_private*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl_hw_start_8168ep(struct rtl8169_private *tp)
{
	rtl8168ep_stop_cmac(tp);

	rtl_set_fifo_size(tp, 0x08, 0x10, 0x02, 0x06);
	rtl8168g_set_pause_thresholds(tp, 0x2f, 0x5f);

	rtl_set_def_aspm_entry_latency(tp);

	rtl_tx_performance_tweak(tp, PCI_EXP_DEVCTL_READRQ_4096B);

	rtl_reset_packet_filter(tp);

	rtl_eri_set_bits(tp, 0xd4, ERIAR_MASK_1111, 0x1f80);

	rtl_eri_write(tp, 0x5f0, ERIAR_MASK_0011, 0x4f87);

	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~RXDV_GATED_EN);

	rtl_eri_write(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_write(tp, 0xb8, ERIAR_MASK_0011, 0x0000);

	rtl8168_config_eee_mac(tp);

	rtl_w0w1_eri(tp, 0x2fc, ERIAR_MASK_0001, 0x01, 0x06);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) & ~TX_10M_PS_EN);

	rtl_pcie_state_l2l3_disable(tp);
}