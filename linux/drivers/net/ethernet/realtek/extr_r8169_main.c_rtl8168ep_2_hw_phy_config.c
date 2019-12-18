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
struct rtl8169_private {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  phy_modify_paged (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8168g_config_eee_phy (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168g_disable_aldps (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168g_phy_adjust_10m_aldps (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_enable_eee (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_w0w1_phy (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl8168ep_2_hw_phy_config(struct rtl8169_private *tp)
{
	rtl8168g_phy_adjust_10m_aldps(tp);

	/* Enable UC LPF tune function */
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x8012);
	rtl_w0w1_phy(tp, 0x14, 0x8000, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* Set rg_sel_sdm_rate */
	phy_modify_paged(tp->phydev, 0x0c42, 0x11, BIT(13), BIT(14));

	/* Channel estimation parameters */
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x80f3);
	rtl_w0w1_phy(tp, 0x14, 0x8b00, ~0x8bff);
	rtl_writephy(tp, 0x13, 0x80f0);
	rtl_w0w1_phy(tp, 0x14, 0x3a00, ~0x3aff);
	rtl_writephy(tp, 0x13, 0x80ef);
	rtl_w0w1_phy(tp, 0x14, 0x0500, ~0x05ff);
	rtl_writephy(tp, 0x13, 0x80f6);
	rtl_w0w1_phy(tp, 0x14, 0x6e00, ~0x6eff);
	rtl_writephy(tp, 0x13, 0x80ec);
	rtl_w0w1_phy(tp, 0x14, 0x6800, ~0x68ff);
	rtl_writephy(tp, 0x13, 0x80ed);
	rtl_w0w1_phy(tp, 0x14, 0x7c00, ~0x7cff);
	rtl_writephy(tp, 0x13, 0x80f2);
	rtl_w0w1_phy(tp, 0x14, 0xf400, ~0xf4ff);
	rtl_writephy(tp, 0x13, 0x80f4);
	rtl_w0w1_phy(tp, 0x14, 0x8500, ~0x85ff);
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x8110);
	rtl_w0w1_phy(tp, 0x14, 0xa800, ~0xa8ff);
	rtl_writephy(tp, 0x13, 0x810f);
	rtl_w0w1_phy(tp, 0x14, 0x1d00, ~0x1dff);
	rtl_writephy(tp, 0x13, 0x8111);
	rtl_w0w1_phy(tp, 0x14, 0xf500, ~0xf5ff);
	rtl_writephy(tp, 0x13, 0x8113);
	rtl_w0w1_phy(tp, 0x14, 0x6100, ~0x61ff);
	rtl_writephy(tp, 0x13, 0x8115);
	rtl_w0w1_phy(tp, 0x14, 0x9200, ~0x92ff);
	rtl_writephy(tp, 0x13, 0x810e);
	rtl_w0w1_phy(tp, 0x14, 0x0400, ~0x04ff);
	rtl_writephy(tp, 0x13, 0x810c);
	rtl_w0w1_phy(tp, 0x14, 0x7c00, ~0x7cff);
	rtl_writephy(tp, 0x13, 0x810b);
	rtl_w0w1_phy(tp, 0x14, 0x5a00, ~0x5aff);
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x80d1);
	rtl_w0w1_phy(tp, 0x14, 0xff00, ~0xffff);
	rtl_writephy(tp, 0x13, 0x80cd);
	rtl_w0w1_phy(tp, 0x14, 0x9e00, ~0x9eff);
	rtl_writephy(tp, 0x13, 0x80d3);
	rtl_w0w1_phy(tp, 0x14, 0x0e00, ~0x0eff);
	rtl_writephy(tp, 0x13, 0x80d5);
	rtl_w0w1_phy(tp, 0x14, 0xca00, ~0xcaff);
	rtl_writephy(tp, 0x13, 0x80d7);
	rtl_w0w1_phy(tp, 0x14, 0x8400, ~0x84ff);

	/* Force PWM-mode */
	rtl_writephy(tp, 0x1f, 0x0bcd);
	rtl_writephy(tp, 0x14, 0x5065);
	rtl_writephy(tp, 0x14, 0xd065);
	rtl_writephy(tp, 0x1f, 0x0bc8);
	rtl_writephy(tp, 0x12, 0x00ed);
	rtl_writephy(tp, 0x1f, 0x0bcd);
	rtl_writephy(tp, 0x14, 0x1065);
	rtl_writephy(tp, 0x14, 0x9065);
	rtl_writephy(tp, 0x14, 0x1065);
	rtl_writephy(tp, 0x1f, 0x0000);

	rtl8168g_disable_aldps(tp);
	rtl8168g_config_eee_phy(tp);
	rtl_enable_eee(tp);
}