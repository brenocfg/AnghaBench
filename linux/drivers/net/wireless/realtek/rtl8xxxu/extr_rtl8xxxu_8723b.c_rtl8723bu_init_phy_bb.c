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
typedef  int u8 ;
typedef  int u16 ;
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_AFE_XTAL_CTRL ; 
 scalar_t__ REG_RF_CTRL ; 
 int /*<<< orphan*/  REG_S0S1_PATH_SWITCH ; 
 scalar_t__ REG_SYS_FUNC ; 
 int RF_ENABLE ; 
 int RF_RSTB ; 
 int RF_SDMRSTB ; 
 int SYS_FUNC_BBRSTB ; 
 int SYS_FUNC_BB_GLB_RSTN ; 
 int SYS_FUNC_DIO_RF ; 
 int /*<<< orphan*/  rtl8723b_phy_1t_init_table ; 
 int /*<<< orphan*/  rtl8xxx_agc_8723bu_table ; 
 int /*<<< orphan*/  rtl8xxxu_init_phy_regs (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read16 (struct rtl8xxxu_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl8xxxu_write16 (struct rtl8xxxu_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,scalar_t__,int) ; 

__attribute__((used)) static void rtl8723bu_init_phy_bb(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u16 val16;

	val16 = rtl8xxxu_read16(priv, REG_SYS_FUNC);
	val16 |= SYS_FUNC_BB_GLB_RSTN | SYS_FUNC_BBRSTB | SYS_FUNC_DIO_RF;
	rtl8xxxu_write16(priv, REG_SYS_FUNC, val16);

	rtl8xxxu_write32(priv, REG_S0S1_PATH_SWITCH, 0x00);

	/* 6. 0x1f[7:0] = 0x07 */
	val8 = RF_ENABLE | RF_RSTB | RF_SDMRSTB;
	rtl8xxxu_write8(priv, REG_RF_CTRL, val8);

	/* Why? */
	rtl8xxxu_write8(priv, REG_SYS_FUNC, 0xe3);
	rtl8xxxu_write8(priv, REG_AFE_XTAL_CTRL + 1, 0x80);
	rtl8xxxu_init_phy_regs(priv, rtl8723b_phy_1t_init_table);

	rtl8xxxu_init_phy_regs(priv, rtl8xxx_agc_8723bu_table);
}