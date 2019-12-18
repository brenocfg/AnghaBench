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
struct ephy_info {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERIAR_MASK_0011 ; 
 int /*<<< orphan*/  FuncEvent ; 
 int /*<<< orphan*/  MCU ; 
 int NOW_IS_OOB ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_READRQ_4096B ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_ephy_init (struct rtl8169_private*,struct ephy_info const*) ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_pcie_state_l2l3_disable (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_reset_packet_filter (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_def_aspm_entry_latency (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_fifo_size (struct rtl8169_private*,int,int,int,int) ; 
 int /*<<< orphan*/  rtl_tx_performance_tweak (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_w0w1_eri (struct rtl8169_private*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl_hw_start_8402(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8402[] = {
		{ 0x19,	0xffff, 0xff64 },
		{ 0x1e,	0, 0x4000 }
	};

	rtl_set_def_aspm_entry_latency(tp);

	/* Force LAN exit from ASPM if Rx/Tx are not idle */
	RTL_W32(tp, FuncEvent, RTL_R32(tp, FuncEvent) | 0x002800);

	RTL_W8(tp, MCU, RTL_R8(tp, MCU) & ~NOW_IS_OOB);

	rtl_ephy_init(tp, e_info_8402);

	rtl_tx_performance_tweak(tp, PCI_EXP_DEVCTL_READRQ_4096B);

	rtl_set_fifo_size(tp, 0x00, 0x00, 0x02, 0x06);
	rtl_reset_packet_filter(tp);
	rtl_eri_write(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_write(tp, 0xb8, ERIAR_MASK_0011, 0x0000);
	rtl_w0w1_eri(tp, 0x0d4, ERIAR_MASK_0011, 0x0e00, 0xff00);

	rtl_pcie_state_l2l3_disable(tp);
}