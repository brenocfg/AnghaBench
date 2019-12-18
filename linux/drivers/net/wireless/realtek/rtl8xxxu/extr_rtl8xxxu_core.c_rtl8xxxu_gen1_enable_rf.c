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
struct rtl8xxxu_priv {int rf_paths; int tx_paths; scalar_t__ rtl_chip; } ;

/* Variables and functions */
 int BIT (int) ; 
 int FPGA_RF_MODE_JAPAN ; 
 int OFDM_RF_PATH_TX_A ; 
 int OFDM_RF_PATH_TX_B ; 
 int OFDM_RF_PATH_TX_MASK ; 
 int /*<<< orphan*/  REG_FPGA0_RF_MODE ; 
 int /*<<< orphan*/  REG_FPGA0_XAB_RF_PARM ; 
 int /*<<< orphan*/  REG_OFDM0_TRX_PATH_ENABLE ; 
 int /*<<< orphan*/  REG_RX_WAIT_CCA ; 
 int /*<<< orphan*/  REG_SPS0_CTRL ; 
 int /*<<< orphan*/  REG_TXPAUSE ; 
 int /*<<< orphan*/  RF6052_REG_AC ; 
 int /*<<< orphan*/  RF_A ; 
 int /*<<< orphan*/  RF_B ; 
 scalar_t__ RTL8191C ; 
 scalar_t__ RTL8192C ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int rtl8xxxu_read8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write_rfreg (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void rtl8xxxu_gen1_enable_rf(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u32 val32;

	val8 = rtl8xxxu_read8(priv, REG_SPS0_CTRL);
	val8 |= BIT(0) | BIT(3);
	rtl8xxxu_write8(priv, REG_SPS0_CTRL, val8);

	val32 = rtl8xxxu_read32(priv, REG_FPGA0_XAB_RF_PARM);
	val32 &= ~(BIT(4) | BIT(5));
	val32 |= BIT(3);
	if (priv->rf_paths == 2) {
		val32 &= ~(BIT(20) | BIT(21));
		val32 |= BIT(19);
	}
	rtl8xxxu_write32(priv, REG_FPGA0_XAB_RF_PARM, val32);

	val32 = rtl8xxxu_read32(priv, REG_OFDM0_TRX_PATH_ENABLE);
	val32 &= ~OFDM_RF_PATH_TX_MASK;
	if (priv->tx_paths == 2)
		val32 |= OFDM_RF_PATH_TX_A | OFDM_RF_PATH_TX_B;
	else if (priv->rtl_chip == RTL8192C || priv->rtl_chip == RTL8191C)
		val32 |= OFDM_RF_PATH_TX_B;
	else
		val32 |= OFDM_RF_PATH_TX_A;
	rtl8xxxu_write32(priv, REG_OFDM0_TRX_PATH_ENABLE, val32);

	val32 = rtl8xxxu_read32(priv, REG_FPGA0_RF_MODE);
	val32 &= ~FPGA_RF_MODE_JAPAN;
	rtl8xxxu_write32(priv, REG_FPGA0_RF_MODE, val32);

	if (priv->rf_paths == 2)
		rtl8xxxu_write32(priv, REG_RX_WAIT_CCA, 0x63db25a0);
	else
		rtl8xxxu_write32(priv, REG_RX_WAIT_CCA, 0x631b25a0);

	rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_AC, 0x32d95);
	if (priv->rf_paths == 2)
		rtl8xxxu_write_rfreg(priv, RF_B, RF6052_REG_AC, 0x32d95);

	rtl8xxxu_write8(priv, REG_TXPAUSE, 0x00);
}