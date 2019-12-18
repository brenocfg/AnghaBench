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
 int BIT (int) ; 
 int /*<<< orphan*/  phy_modify_paged (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  rtl8168g_config_eee_phy (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168g_disable_aldps (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168g_phy_adjust_10m_aldps (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_enable_eee (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_w0w1_phy (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl8168ep_1_hw_phy_config(struct rtl8169_private *tp)
{
	/* Enable PHY auto speed down */
	phy_modify_paged(tp->phydev, 0x0a44, 0x11, 0, BIT(3) | BIT(2));

	rtl8168g_phy_adjust_10m_aldps(tp);

	/* Enable EEE auto-fallback function */
	phy_modify_paged(tp->phydev, 0x0a4b, 0x11, 0, BIT(2));

	/* Enable UC LPF tune function */
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x8012);
	rtl_w0w1_phy(tp, 0x14, 0x8000, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* set rg_sel_sdm_rate */
	phy_modify_paged(tp->phydev, 0x0c42, 0x11, BIT(13), BIT(14));

	rtl8168g_disable_aldps(tp);
	rtl8168g_config_eee_phy(tp);
	rtl_enable_eee(tp);
}