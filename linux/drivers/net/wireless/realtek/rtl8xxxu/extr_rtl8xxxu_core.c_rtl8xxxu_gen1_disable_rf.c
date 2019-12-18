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
typedef  int u32 ;
struct rtl8xxxu_priv {int rf_paths; } ;

/* Variables and functions */
 int BIT (int) ; 
 int FPGA_RF_MODE_JAPAN ; 
 int OFDM_RF_PATH_TX_MASK ; 
 int /*<<< orphan*/  REG_FPGA0_RF_MODE ; 
 int /*<<< orphan*/  REG_FPGA0_XAB_RF_PARM ; 
 int /*<<< orphan*/  REG_OFDM0_TRX_PATH_ENABLE ; 
 int /*<<< orphan*/  REG_RX_WAIT_CCA ; 
 int /*<<< orphan*/  REG_SPS0_CTRL ; 
 int /*<<< orphan*/  RF6052_REG_AC ; 
 int /*<<< orphan*/  RF_A ; 
 int /*<<< orphan*/  RF_B ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write_rfreg (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8xxxu_gen1_disable_rf(struct rtl8xxxu_priv *priv)
{
	u8 sps0;
	u32 val32;

	sps0 = rtl8xxxu_read8(priv, REG_SPS0_CTRL);

	/* RF RX code for preamble power saving */
	val32 = rtl8xxxu_read32(priv, REG_FPGA0_XAB_RF_PARM);
	val32 &= ~(BIT(3) | BIT(4) | BIT(5));
	if (priv->rf_paths == 2)
		val32 &= ~(BIT(19) | BIT(20) | BIT(21));
	rtl8xxxu_write32(priv, REG_FPGA0_XAB_RF_PARM, val32);

	/* Disable TX for four paths */
	val32 = rtl8xxxu_read32(priv, REG_OFDM0_TRX_PATH_ENABLE);
	val32 &= ~OFDM_RF_PATH_TX_MASK;
	rtl8xxxu_write32(priv, REG_OFDM0_TRX_PATH_ENABLE, val32);

	/* Enable power saving */
	val32 = rtl8xxxu_read32(priv, REG_FPGA0_RF_MODE);
	val32 |= FPGA_RF_MODE_JAPAN;
	rtl8xxxu_write32(priv, REG_FPGA0_RF_MODE, val32);

	/* AFE control register to power down bits [30:22] */
	if (priv->rf_paths == 2)
		rtl8xxxu_write32(priv, REG_RX_WAIT_CCA, 0x00db25a0);
	else
		rtl8xxxu_write32(priv, REG_RX_WAIT_CCA, 0x001b25a0);

	/* Power down RF module */
	rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_AC, 0);
	if (priv->rf_paths == 2)
		rtl8xxxu_write_rfreg(priv, RF_B, RF6052_REG_AC, 0);

	sps0 &= ~(BIT(0) | BIT(3));
	rtl8xxxu_write8(priv, REG_SPS0_CTRL, sps0);
}