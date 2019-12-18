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
 int MCU_FW_RAM_SEL ; 
 int /*<<< orphan*/  REG_MCU_FW_DL ; 
 int /*<<< orphan*/  REG_RF_CTRL ; 
 int /*<<< orphan*/  REG_SYS_FUNC ; 
 int /*<<< orphan*/  REG_TX_REPORT_CTRL ; 
 int /*<<< orphan*/  SYS_FUNC_CPU_ENABLE ; 
 int TX_REPORT_CTRL_TIMER_ENABLE ; 
 int /*<<< orphan*/  rtl8192eu_active_to_emu (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8192eu_active_to_lps (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8192eu_emu_to_disabled (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_firmware_self_reset (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_flush_fifo (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_read16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_reset_8051 (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  rtl8xxxu_write16 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8192eu_power_off(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u16 val16;

	rtl8xxxu_flush_fifo(priv);

	val8 = rtl8xxxu_read8(priv, REG_TX_REPORT_CTRL);
	val8 &= ~TX_REPORT_CTRL_TIMER_ENABLE;
	rtl8xxxu_write8(priv, REG_TX_REPORT_CTRL, val8);

	/* Turn off RF */
	rtl8xxxu_write8(priv, REG_RF_CTRL, 0x00);

	rtl8192eu_active_to_lps(priv);

	/* Reset Firmware if running in RAM */
	if (rtl8xxxu_read8(priv, REG_MCU_FW_DL) & MCU_FW_RAM_SEL)
		rtl8xxxu_firmware_self_reset(priv);

	/* Reset MCU */
	val16 = rtl8xxxu_read16(priv, REG_SYS_FUNC);
	val16 &= ~SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_write16(priv, REG_SYS_FUNC, val16);

	/* Reset MCU ready status */
	rtl8xxxu_write8(priv, REG_MCU_FW_DL, 0x00);

	rtl8xxxu_reset_8051(priv);

	rtl8192eu_active_to_emu(priv);
	rtl8192eu_emu_to_disabled(priv);
}