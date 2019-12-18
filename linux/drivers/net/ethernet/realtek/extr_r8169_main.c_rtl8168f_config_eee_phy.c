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
 int /*<<< orphan*/  phy_set_bits (struct phy_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int,int) ; 

__attribute__((used)) static void rtl8168f_config_eee_phy(struct rtl8169_private *tp)
{
	struct phy_device *phydev = tp->phydev;

	phy_write(phydev, 0x1f, 0x0007);
	phy_write(phydev, 0x1e, 0x0020);
	phy_set_bits(phydev, 0x15, BIT(8));

	phy_write(phydev, 0x1f, 0x0005);
	phy_write(phydev, 0x05, 0x8b85);
	phy_set_bits(phydev, 0x06, BIT(13));

	phy_write(phydev, 0x1f, 0x0000);
}