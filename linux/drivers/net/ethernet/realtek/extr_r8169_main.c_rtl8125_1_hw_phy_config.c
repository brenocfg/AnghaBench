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
 int /*<<< orphan*/  phy_clear_bits (struct phy_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_modify (struct phy_device*,int,int,int) ; 
 int /*<<< orphan*/  phy_modify_paged (struct phy_device*,int,int,int,int) ; 
 int /*<<< orphan*/  phy_set_bits (struct phy_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int,int) ; 
 int /*<<< orphan*/  phy_write_paged (struct phy_device*,int,int,int) ; 
 int /*<<< orphan*/  rtl8125_config_eee_phy (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_enable_eee (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8125_1_hw_phy_config(struct rtl8169_private *tp)
{
	struct phy_device *phydev = tp->phydev;

	phy_modify_paged(phydev, 0xad4, 0x10, 0x03ff, 0x0084);
	phy_modify_paged(phydev, 0xad4, 0x17, 0x0000, 0x0010);
	phy_modify_paged(phydev, 0xad1, 0x13, 0x03ff, 0x0006);
	phy_modify_paged(phydev, 0xad3, 0x11, 0x003f, 0x0006);
	phy_modify_paged(phydev, 0xac0, 0x14, 0x0000, 0x1100);
	phy_modify_paged(phydev, 0xac8, 0x15, 0xf000, 0x7000);
	phy_modify_paged(phydev, 0xad1, 0x14, 0x0000, 0x0400);
	phy_modify_paged(phydev, 0xad1, 0x15, 0x0000, 0x03ff);
	phy_modify_paged(phydev, 0xad1, 0x16, 0x0000, 0x03ff);

	phy_write(phydev, 0x1f, 0x0a43);
	phy_write(phydev, 0x13, 0x80ea);
	phy_modify(phydev, 0x14, 0xff00, 0xc400);
	phy_write(phydev, 0x13, 0x80eb);
	phy_modify(phydev, 0x14, 0x0700, 0x0300);
	phy_write(phydev, 0x13, 0x80f8);
	phy_modify(phydev, 0x14, 0xff00, 0x1c00);
	phy_write(phydev, 0x13, 0x80f1);
	phy_modify(phydev, 0x14, 0xff00, 0x3000);
	phy_write(phydev, 0x13, 0x80fe);
	phy_modify(phydev, 0x14, 0xff00, 0xa500);
	phy_write(phydev, 0x13, 0x8102);
	phy_modify(phydev, 0x14, 0xff00, 0x5000);
	phy_write(phydev, 0x13, 0x8105);
	phy_modify(phydev, 0x14, 0xff00, 0x3300);
	phy_write(phydev, 0x13, 0x8100);
	phy_modify(phydev, 0x14, 0xff00, 0x7000);
	phy_write(phydev, 0x13, 0x8104);
	phy_modify(phydev, 0x14, 0xff00, 0xf000);
	phy_write(phydev, 0x13, 0x8106);
	phy_modify(phydev, 0x14, 0xff00, 0x6500);
	phy_write(phydev, 0x13, 0x80dc);
	phy_modify(phydev, 0x14, 0xff00, 0xed00);
	phy_write(phydev, 0x13, 0x80df);
	phy_set_bits(phydev, 0x14, BIT(8));
	phy_write(phydev, 0x13, 0x80e1);
	phy_clear_bits(phydev, 0x14, BIT(8));
	phy_write(phydev, 0x1f, 0x0000);

	phy_modify_paged(phydev, 0xbf0, 0x13, 0x003f, 0x0038);
	phy_write_paged(phydev, 0xa43, 0x13, 0x819f);
	phy_write_paged(phydev, 0xa43, 0x14, 0xd0b6);

	phy_write_paged(phydev, 0xbc3, 0x12, 0x5555);
	phy_modify_paged(phydev, 0xbf0, 0x15, 0x0e00, 0x0a00);
	phy_modify_paged(phydev, 0xa5c, 0x10, 0x0400, 0x0000);
	phy_modify_paged(phydev, 0xa44, 0x11, 0x0000, 0x0800);

	rtl8125_config_eee_phy(tp);
	rtl_enable_eee(tp);
}