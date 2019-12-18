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
typedef  int u32 ;
struct rtl8xxxu_priv {int rf_paths; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  REG_BT_CONTROL_8723BU ; 
 int /*<<< orphan*/  REG_FPGA0_IQK ; 
 int /*<<< orphan*/  REG_IQK_AGC_PTS ; 
 int /*<<< orphan*/  REG_IQK_AGC_RSP ; 
 int /*<<< orphan*/  REG_RX_IQK ; 
 int /*<<< orphan*/  REG_RX_IQK_PI_A ; 
 int /*<<< orphan*/  REG_RX_IQK_PI_B ; 
 int /*<<< orphan*/  REG_RX_IQK_TONE_A ; 
 int /*<<< orphan*/  REG_RX_IQK_TONE_B ; 
 int /*<<< orphan*/  REG_RX_POWER_AFTER_IQK_A_2 ; 
 int /*<<< orphan*/  REG_S0S1_PATH_SWITCH ; 
 int /*<<< orphan*/  REG_TX_IQK ; 
 int /*<<< orphan*/  REG_TX_IQK_PI_A ; 
 int /*<<< orphan*/  REG_TX_IQK_PI_B ; 
 int /*<<< orphan*/  REG_TX_IQK_TONE_A ; 
 int /*<<< orphan*/  REG_TX_IQK_TONE_B ; 
 int /*<<< orphan*/  REG_TX_POWER_AFTER_IQK_A ; 
 int /*<<< orphan*/  REG_TX_POWER_BEFORE_IQK_A ; 
 int /*<<< orphan*/  RF6052_REG_RCK_OS ; 
 int /*<<< orphan*/  RF6052_REG_TXPA_G1 ; 
 int /*<<< orphan*/  RF6052_REG_TXPA_G2 ; 
 int /*<<< orphan*/  RF6052_REG_WE_LUT ; 
 int /*<<< orphan*/  RF_A ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read_rfreg (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write_rfreg (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl8723bu_iqk_path_a(struct rtl8xxxu_priv *priv)
{
	u32 reg_eac, reg_e94, reg_e9c, path_sel, val32;
	int result = 0;

	path_sel = rtl8xxxu_read32(priv, REG_S0S1_PATH_SWITCH);

	/*
	 * Leave IQK mode
	 */
	val32 = rtl8xxxu_read32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	rtl8xxxu_write32(priv, REG_FPGA0_IQK, val32);

	/*
	 * Enable path A PA in TX IQK mode
	 */
	val32 = rtl8xxxu_read_rfreg(priv, RF_A, RF6052_REG_WE_LUT);
	val32 |= 0x80000;
	rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_WE_LUT, val32);
	rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_RCK_OS, 0x20000);
	rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_TXPA_G1, 0x0003f);
	rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_TXPA_G2, 0xc7f87);

	/*
	 * Tx IQK setting
	 */
	rtl8xxxu_write32(priv, REG_TX_IQK, 0x01007c00);
	rtl8xxxu_write32(priv, REG_RX_IQK, 0x01004800);

	/* path-A IQK setting */
	rtl8xxxu_write32(priv, REG_TX_IQK_TONE_A, 0x18008c1c);
	rtl8xxxu_write32(priv, REG_RX_IQK_TONE_A, 0x38008c1c);
	rtl8xxxu_write32(priv, REG_TX_IQK_TONE_B, 0x38008c1c);
	rtl8xxxu_write32(priv, REG_RX_IQK_TONE_B, 0x38008c1c);

	rtl8xxxu_write32(priv, REG_TX_IQK_PI_A, 0x821403ea);
	rtl8xxxu_write32(priv, REG_RX_IQK_PI_A, 0x28110000);
	rtl8xxxu_write32(priv, REG_TX_IQK_PI_B, 0x82110000);
	rtl8xxxu_write32(priv, REG_RX_IQK_PI_B, 0x28110000);

	/* LO calibration setting */
	rtl8xxxu_write32(priv, REG_IQK_AGC_RSP, 0x00462911);

	/*
	 * Enter IQK mode
	 */
	val32 = rtl8xxxu_read32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	val32 |= 0x80800000;
	rtl8xxxu_write32(priv, REG_FPGA0_IQK, val32);

	/*
	 * The vendor driver indicates the USB module is always using
	 * S0S1 path 1 for the 8723bu. This may be different for 8192eu
	 */
	if (priv->rf_paths > 1)
		rtl8xxxu_write32(priv, REG_S0S1_PATH_SWITCH, 0x00000000);
	else
		rtl8xxxu_write32(priv, REG_S0S1_PATH_SWITCH, 0x00000280);

	/*
	 * Bit 12 seems to be BT_GRANT, and is only found in the 8723bu.
	 * No trace of this in the 8192eu or 8188eu vendor drivers.
	 */
	rtl8xxxu_write32(priv, REG_BT_CONTROL_8723BU, 0x00000800);

	/* One shot, path A LOK & IQK */
	rtl8xxxu_write32(priv, REG_IQK_AGC_PTS, 0xf9000000);
	rtl8xxxu_write32(priv, REG_IQK_AGC_PTS, 0xf8000000);

	mdelay(1);

	/* Restore Ant Path */
	rtl8xxxu_write32(priv, REG_S0S1_PATH_SWITCH, path_sel);
#ifdef RTL8723BU_BT
	/* GNT_BT = 1 */
	rtl8xxxu_write32(priv, REG_BT_CONTROL_8723BU, 0x00001800);
#endif

	/*
	 * Leave IQK mode
	 */
	val32 = rtl8xxxu_read32(priv, REG_FPGA0_IQK);
	val32 &= 0x000000ff;
	rtl8xxxu_write32(priv, REG_FPGA0_IQK, val32);

	/* Check failed */
	reg_eac = rtl8xxxu_read32(priv, REG_RX_POWER_AFTER_IQK_A_2);
	reg_e94 = rtl8xxxu_read32(priv, REG_TX_POWER_BEFORE_IQK_A);
	reg_e9c = rtl8xxxu_read32(priv, REG_TX_POWER_AFTER_IQK_A);

	val32 = (reg_e9c >> 16) & 0x3ff;
	if (val32 & 0x200)
		val32 = 0x400 - val32;

	if (!(reg_eac & BIT(28)) &&
	    ((reg_e94 & 0x03ff0000) != 0x01420000) &&
	    ((reg_e9c & 0x03ff0000) != 0x00420000) &&
	    ((reg_e94 & 0x03ff0000)  < 0x01100000) &&
	    ((reg_e94 & 0x03ff0000)  > 0x00f00000) &&
	    val32 < 0xf)
		result |= 0x01;
	else	/* If TX not OK, ignore RX */
		goto out;

out:
	return result;
}