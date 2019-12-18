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
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int RF6052_REG_MODE_AG ; 
 int /*<<< orphan*/  RF_A ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtl8723bu_radioa_1t_init_table ; 
 int rtl8xxxu_init_phy_rf (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write_rfreg (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rtl8723bu_init_phy_rf(struct rtl8xxxu_priv *priv)
{
	int ret;

	ret = rtl8xxxu_init_phy_rf(priv, rtl8723bu_radioa_1t_init_table, RF_A);
	/*
	 * PHY LCK
	 */
	rtl8xxxu_write_rfreg(priv, RF_A, 0xb0, 0xdfbe0);
	rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_MODE_AG, 0x8c01);
	msleep(200);
	rtl8xxxu_write_rfreg(priv, RF_A, 0xb0, 0xdffe0);

	return ret;
}