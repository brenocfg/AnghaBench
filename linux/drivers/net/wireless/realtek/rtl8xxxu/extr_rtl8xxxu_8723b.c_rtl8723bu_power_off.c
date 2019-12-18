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
typedef  int /*<<< orphan*/  u16 ;
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MCU_FW_RAM_SEL ; 
 scalar_t__ REG_APS_FSMCO ; 
 scalar_t__ REG_CR ; 
 scalar_t__ REG_GPIO_INTM ; 
 scalar_t__ REG_MCU_FW_DL ; 
 int /*<<< orphan*/  REG_SYS_FUNC ; 
 scalar_t__ REG_TX_REPORT_CTRL ; 
 int /*<<< orphan*/  SYS_FUNC_CPU_ENABLE ; 
 int TX_REPORT_CTRL_TIMER_ENABLE ; 
 int /*<<< orphan*/  rtl8723bu_active_to_emu (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_active_to_lps (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_firmware_self_reset (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_flush_fifo (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_read16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read8 (struct rtl8xxxu_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl8xxxu_write16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,scalar_t__,int) ; 

__attribute__((used)) static void rtl8723bu_power_off(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u16 val16;

	rtl8xxxu_flush_fifo(priv);

	/*
	 * Disable TX report timer
	 */
	val8 = rtl8xxxu_read8(priv, REG_TX_REPORT_CTRL);
	val8 &= ~TX_REPORT_CTRL_TIMER_ENABLE;
	rtl8xxxu_write8(priv, REG_TX_REPORT_CTRL, val8);

	rtl8xxxu_write8(priv, REG_CR, 0x0000);

	rtl8xxxu_active_to_lps(priv);

	/* Reset Firmware if running in RAM */
	if (rtl8xxxu_read8(priv, REG_MCU_FW_DL) & MCU_FW_RAM_SEL)
		rtl8xxxu_firmware_self_reset(priv);

	/* Reset MCU */
	val16 = rtl8xxxu_read16(priv, REG_SYS_FUNC);
	val16 &= ~SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_write16(priv, REG_SYS_FUNC, val16);

	/* Reset MCU ready status */
	rtl8xxxu_write8(priv, REG_MCU_FW_DL, 0x00);

	rtl8723bu_active_to_emu(priv);

	val8 = rtl8xxxu_read8(priv, REG_APS_FSMCO + 1);
	val8 |= BIT(3); /* APS_FSMCO_HW_SUSPEND */
	rtl8xxxu_write8(priv, REG_APS_FSMCO + 1, val8);

	/* 0x48[16] = 1 to enable GPIO9 as EXT wakeup */
	val8 = rtl8xxxu_read8(priv, REG_GPIO_INTM + 2);
	val8 |= BIT(0);
	rtl8xxxu_write8(priv, REG_GPIO_INTM + 2, val8);
}