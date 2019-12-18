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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct r8192_priv {scalar_t__ IC_Cut; scalar_t__ rf_type; int* AntennaTxPwDiff; int CrystalCap; } ;
struct net_device {int dummy; } ;
typedef  enum rf90_radio_path { ____Placeholder_rf90_radio_path } rf90_radio_path ;
typedef  enum hw90_block { ____Placeholder_hw90_block } hw90_block ;

/* Variables and functions */
 int /*<<< orphan*/  BB_GLOBAL_RESET ; 
 scalar_t__ BB_GLOBAL_RESET_BIT ; 
 int /*<<< orphan*/  BaseBand_Config_AGC_TAB ; 
 int /*<<< orphan*/  BaseBand_Config_PHY_REG ; 
 int COMP_ERR ; 
 int COMP_PHY ; 
 int /*<<< orphan*/  CPU_GEN ; 
 int CPU_GEN_BB_RST ; 
 scalar_t__ HW90_BLOCK_PHY0 ; 
 scalar_t__ HW90_BLOCK_PHY1 ; 
 scalar_t__ RF_2T4R ; 
 int /*<<< orphan*/  RT_TRACE (int,char*,scalar_t__) ; 
 scalar_t__ VERSION_8190_BD ; 
 int /*<<< orphan*/  _rtl92e_phy_config_bb (struct net_device*,int /*<<< orphan*/ ) ; 
 int bCCKEn ; 
 int bOFDMEn ; 
 int bXBTxAGC ; 
 int bXCTxAGC ; 
 int bXDTxAGC ; 
 int bXtalCap92x ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter1 ; 
 int /*<<< orphan*/  rFPGA0_RFMOD ; 
 int /*<<< orphan*/  rFPGA0_TxGainStage ; 
 int rtl92e_check_bb_and_rf (struct net_device*,int,int) ; 
 scalar_t__ rtl92e_readb (struct net_device*,int /*<<< orphan*/ ) ; 
 int rtl92e_readl (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_set_bb_reg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtl92e_writel (struct net_device*,int /*<<< orphan*/ ,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static bool _rtl92e_bb_config_para_file(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	bool rtStatus = true;
	u8 bRegValue = 0, eCheckItem = 0;
	u32 dwRegValue = 0;

	bRegValue = rtl92e_readb(dev, BB_GLOBAL_RESET);
	rtl92e_writeb(dev, BB_GLOBAL_RESET, (bRegValue|BB_GLOBAL_RESET_BIT));

	dwRegValue = rtl92e_readl(dev, CPU_GEN);
	rtl92e_writel(dev, CPU_GEN, (dwRegValue&(~CPU_GEN_BB_RST)));

	for (eCheckItem = (enum hw90_block)HW90_BLOCK_PHY0;
	     eCheckItem <= HW90_BLOCK_PHY1; eCheckItem++) {
		rtStatus  = rtl92e_check_bb_and_rf(dev,
						   (enum hw90_block)eCheckItem,
						   (enum rf90_radio_path)0);
		if (!rtStatus) {
			RT_TRACE((COMP_ERR | COMP_PHY),
				 "rtl92e_config_rf():Check PHY%d Fail!!\n",
				 eCheckItem-1);
			return rtStatus;
		}
	}
	rtl92e_set_bb_reg(dev, rFPGA0_RFMOD, bCCKEn|bOFDMEn, 0x0);
	_rtl92e_phy_config_bb(dev, BaseBand_Config_PHY_REG);

	dwRegValue = rtl92e_readl(dev, CPU_GEN);
	rtl92e_writel(dev, CPU_GEN, (dwRegValue|CPU_GEN_BB_RST));

	_rtl92e_phy_config_bb(dev, BaseBand_Config_AGC_TAB);

	if (priv->IC_Cut  > VERSION_8190_BD) {
		if (priv->rf_type == RF_2T4R)
			dwRegValue = priv->AntennaTxPwDiff[2]<<8 |
				      priv->AntennaTxPwDiff[1]<<4 |
				      priv->AntennaTxPwDiff[0];
		else
			dwRegValue = 0x0;
		rtl92e_set_bb_reg(dev, rFPGA0_TxGainStage,
				  (bXBTxAGC|bXCTxAGC|bXDTxAGC), dwRegValue);


		dwRegValue = priv->CrystalCap;
		rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1, bXtalCap92x,
				  dwRegValue);
	}

	return rtStatus;
}