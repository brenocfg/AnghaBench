#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct rtl8xxxu_priv {int tx_paths; int rx_paths; int xtalk; scalar_t__ rtl_chip; scalar_t__ has_xtalk; TYPE_1__* fops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_phy_bb ) (struct rtl8xxxu_priv*) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int CCK0_AFE_RX_ANT_B ; 
 int CCK0_AFE_RX_MASK ; 
 int OFDM_RF_PATH_RX_A ; 
 int OFDM_RF_PATH_RX_B ; 
 int OFDM_RF_PATH_RX_MASK ; 
 int OFDM_RF_PATH_TX_B ; 
 int OFDM_RF_PATH_TX_MASK ; 
 int /*<<< orphan*/  REG_AFE_XTAL_CTRL ; 
 int /*<<< orphan*/  REG_CCK0_AFE_SETTING ; 
 int /*<<< orphan*/  REG_FPGA0_TX_INFO ; 
 int /*<<< orphan*/  REG_FPGA1_TX_INFO ; 
 int /*<<< orphan*/  REG_MAC_PHY_CTRL ; 
 int /*<<< orphan*/  REG_OFDM0_AGC_PARM1 ; 
 int /*<<< orphan*/  REG_OFDM0_TRX_PATH_ENABLE ; 
 int /*<<< orphan*/  REG_TX_CCK_BBON ; 
 int /*<<< orphan*/  REG_TX_CCK_RFON ; 
 int /*<<< orphan*/  REG_TX_OFDM_BBON ; 
 int /*<<< orphan*/  REG_TX_OFDM_RFON ; 
 int /*<<< orphan*/  REG_TX_TO_TX ; 
 scalar_t__ RTL8192E ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct rtl8xxxu_priv*) ; 

__attribute__((used)) static int rtl8xxxu_init_phy_bb(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u32 val32;

	priv->fops->init_phy_bb(priv);

	if (priv->tx_paths == 1 && priv->rx_paths == 2) {
		/*
		 * For 1T2R boards, patch the registers.
		 *
		 * It looks like 8191/2 1T2R boards use path B for TX
		 */
		val32 = rtl8xxxu_read32(priv, REG_FPGA0_TX_INFO);
		val32 &= ~(BIT(0) | BIT(1));
		val32 |= BIT(1);
		rtl8xxxu_write32(priv, REG_FPGA0_TX_INFO, val32);

		val32 = rtl8xxxu_read32(priv, REG_FPGA1_TX_INFO);
		val32 &= ~0x300033;
		val32 |= 0x200022;
		rtl8xxxu_write32(priv, REG_FPGA1_TX_INFO, val32);

		val32 = rtl8xxxu_read32(priv, REG_CCK0_AFE_SETTING);
		val32 &= ~CCK0_AFE_RX_MASK;
		val32 &= 0x00ffffff;
		val32 |= 0x40000000;
		val32 |= CCK0_AFE_RX_ANT_B;
		rtl8xxxu_write32(priv, REG_CCK0_AFE_SETTING, val32);

		val32 = rtl8xxxu_read32(priv, REG_OFDM0_TRX_PATH_ENABLE);
		val32 &= ~(OFDM_RF_PATH_RX_MASK | OFDM_RF_PATH_TX_MASK);
		val32 |= (OFDM_RF_PATH_RX_A | OFDM_RF_PATH_RX_B |
			  OFDM_RF_PATH_TX_B);
		rtl8xxxu_write32(priv, REG_OFDM0_TRX_PATH_ENABLE, val32);

		val32 = rtl8xxxu_read32(priv, REG_OFDM0_AGC_PARM1);
		val32 &= ~(BIT(4) | BIT(5));
		val32 |= BIT(4);
		rtl8xxxu_write32(priv, REG_OFDM0_AGC_PARM1, val32);

		val32 = rtl8xxxu_read32(priv, REG_TX_CCK_RFON);
		val32 &= ~(BIT(27) | BIT(26));
		val32 |= BIT(27);
		rtl8xxxu_write32(priv, REG_TX_CCK_RFON, val32);

		val32 = rtl8xxxu_read32(priv, REG_TX_CCK_BBON);
		val32 &= ~(BIT(27) | BIT(26));
		val32 |= BIT(27);
		rtl8xxxu_write32(priv, REG_TX_CCK_BBON, val32);

		val32 = rtl8xxxu_read32(priv, REG_TX_OFDM_RFON);
		val32 &= ~(BIT(27) | BIT(26));
		val32 |= BIT(27);
		rtl8xxxu_write32(priv, REG_TX_OFDM_RFON, val32);

		val32 = rtl8xxxu_read32(priv, REG_TX_OFDM_BBON);
		val32 &= ~(BIT(27) | BIT(26));
		val32 |= BIT(27);
		rtl8xxxu_write32(priv, REG_TX_OFDM_BBON, val32);

		val32 = rtl8xxxu_read32(priv, REG_TX_TO_TX);
		val32 &= ~(BIT(27) | BIT(26));
		val32 |= BIT(27);
		rtl8xxxu_write32(priv, REG_TX_TO_TX, val32);
	}

	if (priv->has_xtalk) {
		val32 = rtl8xxxu_read32(priv, REG_MAC_PHY_CTRL);

		val8 = priv->xtalk;
		val32 &= 0xff000fff;
		val32 |= ((val8 | (val8 << 6)) << 12);

		rtl8xxxu_write32(priv, REG_MAC_PHY_CTRL, val32);
	}

	if (priv->rtl_chip == RTL8192E)
		rtl8xxxu_write32(priv, REG_AFE_XTAL_CTRL, 0x000f81fb);

	return 0;
}