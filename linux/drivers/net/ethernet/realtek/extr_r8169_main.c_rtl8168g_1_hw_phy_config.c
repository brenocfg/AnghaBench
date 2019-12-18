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
 int phy_read_paged (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl8168g_config_eee_phy (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168g_disable_aldps (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168g_phy_adjust_10m_aldps (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_apply_firmware (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_enable_eee (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_w0w1_phy (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl8168g_1_hw_phy_config(struct rtl8169_private *tp)
{
	int ret;

	rtl_apply_firmware(tp);

	ret = phy_read_paged(tp->phydev, 0x0a46, 0x10);
	if (ret & BIT(8))
		phy_modify_paged(tp->phydev, 0x0bcc, 0x12, BIT(15), 0);
	else
		phy_modify_paged(tp->phydev, 0x0bcc, 0x12, 0, BIT(15));

	ret = phy_read_paged(tp->phydev, 0x0a46, 0x13);
	if (ret & BIT(8))
		phy_modify_paged(tp->phydev, 0x0c41, 0x15, 0, BIT(1));
	else
		phy_modify_paged(tp->phydev, 0x0c41, 0x15, BIT(1), 0);

	/* Enable PHY auto speed down */
	phy_modify_paged(tp->phydev, 0x0a44, 0x11, 0, BIT(3) | BIT(2));

	rtl8168g_phy_adjust_10m_aldps(tp);

	/* EEE auto-fallback function */
	phy_modify_paged(tp->phydev, 0x0a4b, 0x11, 0, BIT(2));

	/* Enable UC LPF tune function */
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x8012);
	rtl_w0w1_phy(tp, 0x14, 0x8000, 0x0000);

	phy_modify_paged(tp->phydev, 0x0c42, 0x11, BIT(13), BIT(14));

	/* Improve SWR Efficiency */
	rtl_writephy(tp, 0x1f, 0x0bcd);
	rtl_writephy(tp, 0x14, 0x5065);
	rtl_writephy(tp, 0x14, 0xd065);
	rtl_writephy(tp, 0x1f, 0x0bc8);
	rtl_writephy(tp, 0x11, 0x5655);
	rtl_writephy(tp, 0x1f, 0x0bcd);
	rtl_writephy(tp, 0x14, 0x1065);
	rtl_writephy(tp, 0x14, 0x9065);
	rtl_writephy(tp, 0x14, 0x1065);
	rtl_writephy(tp, 0x1f, 0x0000);

	rtl8168g_disable_aldps(tp);
	rtl8168g_config_eee_phy(tp);
	rtl_enable_eee(tp);
}