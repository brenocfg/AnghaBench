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
struct rtl8169_private {struct phy_device* phydev; } ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  phy_modify_paged (struct phy_device*,int,int,int,int) ; 
 int /*<<< orphan*/  phy_set_bits (struct phy_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int,int) ; 
 int /*<<< orphan*/  phy_write_paged (struct phy_device*,int,int,int) ; 
 int /*<<< orphan*/  rtl8125_config_eee_phy (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_apply_firmware (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_enable_eee (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8125_2_hw_phy_config(struct rtl8169_private *tp)
{
	struct phy_device *phydev = tp->phydev;
	int i;

	phy_modify_paged(phydev, 0xad4, 0x17, 0x0000, 0x0010);
	phy_modify_paged(phydev, 0xad1, 0x13, 0x03ff, 0x03ff);
	phy_modify_paged(phydev, 0xad3, 0x11, 0x003f, 0x0006);
	phy_modify_paged(phydev, 0xac0, 0x14, 0x1100, 0x0000);
	phy_modify_paged(phydev, 0xacc, 0x10, 0x0003, 0x0002);
	phy_modify_paged(phydev, 0xad4, 0x10, 0x00e7, 0x0044);
	phy_modify_paged(phydev, 0xac1, 0x12, 0x0080, 0x0000);
	phy_modify_paged(phydev, 0xac8, 0x10, 0x0300, 0x0000);
	phy_modify_paged(phydev, 0xac5, 0x17, 0x0007, 0x0002);
	phy_write_paged(phydev, 0xad4, 0x16, 0x00a8);
	phy_write_paged(phydev, 0xac5, 0x16, 0x01ff);
	phy_modify_paged(phydev, 0xac8, 0x15, 0x00f0, 0x0030);

	phy_write(phydev, 0x1f, 0x0b87);
	phy_write(phydev, 0x16, 0x80a2);
	phy_write(phydev, 0x17, 0x0153);
	phy_write(phydev, 0x16, 0x809c);
	phy_write(phydev, 0x17, 0x0153);
	phy_write(phydev, 0x1f, 0x0000);

	phy_write(phydev, 0x1f, 0x0a43);
	phy_write(phydev, 0x13, 0x81B3);
	phy_write(phydev, 0x14, 0x0043);
	phy_write(phydev, 0x14, 0x00A7);
	phy_write(phydev, 0x14, 0x00D6);
	phy_write(phydev, 0x14, 0x00EC);
	phy_write(phydev, 0x14, 0x00F6);
	phy_write(phydev, 0x14, 0x00FB);
	phy_write(phydev, 0x14, 0x00FD);
	phy_write(phydev, 0x14, 0x00FF);
	phy_write(phydev, 0x14, 0x00BB);
	phy_write(phydev, 0x14, 0x0058);
	phy_write(phydev, 0x14, 0x0029);
	phy_write(phydev, 0x14, 0x0013);
	phy_write(phydev, 0x14, 0x0009);
	phy_write(phydev, 0x14, 0x0004);
	phy_write(phydev, 0x14, 0x0002);
	for (i = 0; i < 25; i++)
		phy_write(phydev, 0x14, 0x0000);

	phy_write(phydev, 0x13, 0x8257);
	phy_write(phydev, 0x14, 0x020F);

	phy_write(phydev, 0x13, 0x80EA);
	phy_write(phydev, 0x14, 0x7843);
	phy_write(phydev, 0x1f, 0x0000);

	rtl_apply_firmware(tp);

	phy_modify_paged(phydev, 0xd06, 0x14, 0x0000, 0x2000);

	phy_write(phydev, 0x1f, 0x0a43);
	phy_write(phydev, 0x13, 0x81a2);
	phy_set_bits(phydev, 0x14, BIT(8));
	phy_write(phydev, 0x1f, 0x0000);

	phy_modify_paged(phydev, 0xb54, 0x16, 0xff00, 0xdb00);
	phy_modify_paged(phydev, 0xa45, 0x12, 0x0001, 0x0000);
	phy_modify_paged(phydev, 0xa5d, 0x12, 0x0000, 0x0020);
	phy_modify_paged(phydev, 0xad4, 0x17, 0x0010, 0x0000);
	phy_modify_paged(phydev, 0xa86, 0x15, 0x0001, 0x0000);
	phy_modify_paged(phydev, 0xa44, 0x11, 0x0000, 0x0800);

	rtl8125_config_eee_phy(tp);
	rtl_enable_eee(tp);
}