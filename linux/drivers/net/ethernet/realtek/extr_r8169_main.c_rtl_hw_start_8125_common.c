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
 int Config1 ; 
 int /*<<< orphan*/  MISC ; 
 int RTL_R16 (struct rtl8169_private*,int) ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int RTL_R8 (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int,int) ; 
 int RXDV_GATED_EN ; 
 int /*<<< orphan*/  r8168_mac_ocp_modify (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  r8168_mac_ocp_write (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl8125_config_eee_mac (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_mac_ocp_e00e_cond ; 
 int /*<<< orphan*/  rtl_pcie_state_l2l3_disable (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_udelay_loop_wait_low (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rtl_hw_start_8125_common(struct rtl8169_private *tp)
{
	rtl_pcie_state_l2l3_disable(tp);

	RTL_W16(tp, 0x382, 0x221b);
	RTL_W8(tp, 0x4500, 0);
	RTL_W16(tp, 0x4800, 0);

	/* disable UPS */
	r8168_mac_ocp_modify(tp, 0xd40a, 0x0010, 0x0000);

	RTL_W8(tp, Config1, RTL_R8(tp, Config1) & ~0x10);

	r8168_mac_ocp_write(tp, 0xc140, 0xffff);
	r8168_mac_ocp_write(tp, 0xc142, 0xffff);

	r8168_mac_ocp_modify(tp, 0xd3e2, 0x0fff, 0x03a9);
	r8168_mac_ocp_modify(tp, 0xd3e4, 0x00ff, 0x0000);
	r8168_mac_ocp_modify(tp, 0xe860, 0x0000, 0x0080);

	/* disable new tx descriptor format */
	r8168_mac_ocp_modify(tp, 0xeb58, 0x0001, 0x0000);

	r8168_mac_ocp_modify(tp, 0xe614, 0x0700, 0x0400);
	r8168_mac_ocp_modify(tp, 0xe63e, 0x0c30, 0x0020);
	r8168_mac_ocp_modify(tp, 0xc0b4, 0x0000, 0x000c);
	r8168_mac_ocp_modify(tp, 0xeb6a, 0x00ff, 0x0033);
	r8168_mac_ocp_modify(tp, 0xeb50, 0x03e0, 0x0040);
	r8168_mac_ocp_modify(tp, 0xe056, 0x00f0, 0x0030);
	r8168_mac_ocp_modify(tp, 0xe040, 0x1000, 0x0000);
	r8168_mac_ocp_modify(tp, 0xe0c0, 0x4f0f, 0x4403);
	r8168_mac_ocp_modify(tp, 0xe052, 0x0080, 0x0067);
	r8168_mac_ocp_modify(tp, 0xc0ac, 0x0080, 0x1f00);
	r8168_mac_ocp_modify(tp, 0xd430, 0x0fff, 0x047f);
	r8168_mac_ocp_modify(tp, 0xe84c, 0x0000, 0x00c0);
	r8168_mac_ocp_modify(tp, 0xea1c, 0x0004, 0x0000);
	r8168_mac_ocp_modify(tp, 0xeb54, 0x0000, 0x0001);
	udelay(1);
	r8168_mac_ocp_modify(tp, 0xeb54, 0x0001, 0x0000);
	RTL_W16(tp, 0x1880, RTL_R16(tp, 0x1880) & ~0x0030);

	r8168_mac_ocp_write(tp, 0xe098, 0xc302);

	rtl_udelay_loop_wait_low(tp, &rtl_mac_ocp_e00e_cond, 1000, 10);

	rtl8125_config_eee_mac(tp);

	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~RXDV_GATED_EN);
	udelay(10);
}