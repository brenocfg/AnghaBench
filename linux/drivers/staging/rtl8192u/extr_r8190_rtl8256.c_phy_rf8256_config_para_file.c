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
typedef  size_t u8 ;
typedef  int u32 ;
struct r8192_priv {size_t NumTotalRFPath; TYPE_1__* PHYRegDef; } ;
struct net_device {int dummy; } ;
typedef  enum rf90_radio_path_e { ____Placeholder_rf90_radio_path_e } rf90_radio_path_e ;
struct TYPE_2__ {int /*<<< orphan*/  rfintfs; int /*<<< orphan*/  rfHSSIPara2; int /*<<< orphan*/  rfintfo; int /*<<< orphan*/  rfintfe; } ;
typedef  TYPE_1__ BB_REGISTER_DEFINITION_T ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_PHY ; 
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  HW90_BLOCK_RF ; 
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int b3WireAddressLength ; 
 int b3WireDataLength ; 
 int /*<<< orphan*/  bMask12Bits ; 
 int bRFSI_RFENV ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int rtl8192_QueryBBReg (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8192_phy_CheckIsLegalRFPath (struct net_device*,size_t) ; 
 size_t rtl8192_phy_ConfigRFWithHeaderFile (struct net_device*,int) ; 
 int rtl8192_phy_QueryRFReg (struct net_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_phy_SetRFReg (struct net_device*,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rtl8192_phy_checkBBAndRF (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void phy_rf8256_config_para_file(struct net_device *dev)
{
	u32	u4RegValue = 0;
	u8	eRFPath;
	BB_REGISTER_DEFINITION_T	*pPhyReg;
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32	RegOffSetToBeCheck = 0x3;
	u32	RegValueToBeCheck = 0x7f1;
	u32	RF3_Final_Value = 0;
	u8	ConstRetryTimes = 5, RetryTimes = 5;
	u8 ret = 0;
	/* Initialize RF */
	for (eRFPath = (enum rf90_radio_path_e)RF90_PATH_A; eRFPath < priv->NumTotalRFPath; eRFPath++) {
		if (!rtl8192_phy_CheckIsLegalRFPath(dev, eRFPath))
			continue;

		pPhyReg = &priv->PHYRegDef[eRFPath];

		/* Joseph test for shorten RF config
		 * pHalData->RfReg0Value[eRFPath] =  rtl8192_phy_QueryRFReg(dev, (enum rf90_radio_path_e)eRFPath, rGlobalCtrl, bMaskDWord);
		 * ----Store original RFENV control type
		 */
		switch (eRFPath) {
		case RF90_PATH_A:
		case RF90_PATH_C:
			u4RegValue = rtl8192_QueryBBReg(dev, pPhyReg->rfintfs, bRFSI_RFENV);
			break;
		case RF90_PATH_B:
		case RF90_PATH_D:
			u4RegValue = rtl8192_QueryBBReg(dev, pPhyReg->rfintfs, bRFSI_RFENV << 16);
			break;
		}

		/*----Set RF_ENV enable----*/
		rtl8192_setBBreg(dev, pPhyReg->rfintfe, bRFSI_RFENV << 16, 0x1);

		/*----Set RF_ENV output high----*/
		rtl8192_setBBreg(dev, pPhyReg->rfintfo, bRFSI_RFENV, 0x1);

		/* Set bit number of Address and Data for RF register */
		rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2, b3WireAddressLength, 0x0);	/* Set 0 to 4 bits for Z-serial and set 1 to 6 bits for 8258 */
		rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2, b3WireDataLength, 0x0);	/* Set 0 to 12 bits for Z-serial and 8258, and set 1 to 14 bits for ??? */

		rtl8192_phy_SetRFReg(dev, (enum rf90_radio_path_e)eRFPath, 0x0, bMask12Bits, 0xbf);

		/* Check RF block (for FPGA platform only)----
		 * TODO: this function should be removed on ASIC , Emily 2007.2.2
		 */
		if (rtl8192_phy_checkBBAndRF(dev, HW90_BLOCK_RF, (enum rf90_radio_path_e)eRFPath)) {
			RT_TRACE(COMP_ERR, "phy_rf8256_config():Check Radio[%d] Fail!!\n", eRFPath);
			goto phy_RF8256_Config_ParaFile_Fail;
		}

		RetryTimes = ConstRetryTimes;
		RF3_Final_Value = 0;
		/*----Initialize RF fom connfiguration file----*/
		switch (eRFPath) {
		case RF90_PATH_A:
			while (RF3_Final_Value != RegValueToBeCheck && RetryTimes != 0) {
				ret = rtl8192_phy_ConfigRFWithHeaderFile(dev, (enum rf90_radio_path_e)eRFPath);
				RF3_Final_Value = rtl8192_phy_QueryRFReg(dev, (enum rf90_radio_path_e)eRFPath, RegOffSetToBeCheck, bMask12Bits);
				RT_TRACE(COMP_RF, "RF %d %d register final value: %x\n", eRFPath, RegOffSetToBeCheck, RF3_Final_Value);
				RetryTimes--;
			}
			break;
		case RF90_PATH_B:
			while (RF3_Final_Value != RegValueToBeCheck && RetryTimes != 0) {
				ret = rtl8192_phy_ConfigRFWithHeaderFile(dev, (enum rf90_radio_path_e)eRFPath);
				RF3_Final_Value = rtl8192_phy_QueryRFReg(dev, (enum rf90_radio_path_e)eRFPath, RegOffSetToBeCheck, bMask12Bits);
				RT_TRACE(COMP_RF, "RF %d %d register final value: %x\n", eRFPath, RegOffSetToBeCheck, RF3_Final_Value);
				RetryTimes--;
			}
			break;
		case RF90_PATH_C:
			while (RF3_Final_Value != RegValueToBeCheck && RetryTimes != 0) {
				ret = rtl8192_phy_ConfigRFWithHeaderFile(dev, (enum rf90_radio_path_e)eRFPath);
				RF3_Final_Value = rtl8192_phy_QueryRFReg(dev, (enum rf90_radio_path_e)eRFPath, RegOffSetToBeCheck, bMask12Bits);
				RT_TRACE(COMP_RF, "RF %d %d register final value: %x\n", eRFPath, RegOffSetToBeCheck, RF3_Final_Value);
				RetryTimes--;
			}
			break;
		case RF90_PATH_D:
			while (RF3_Final_Value != RegValueToBeCheck && RetryTimes != 0) {
				ret = rtl8192_phy_ConfigRFWithHeaderFile(dev, (enum rf90_radio_path_e)eRFPath);
				RF3_Final_Value = rtl8192_phy_QueryRFReg(dev, (enum rf90_radio_path_e)eRFPath, RegOffSetToBeCheck, bMask12Bits);
				RT_TRACE(COMP_RF, "RF %d %d register final value: %x\n", eRFPath, RegOffSetToBeCheck, RF3_Final_Value);
				RetryTimes--;
			}
			break;
		}

		/*----Restore RFENV control type----*/
		switch (eRFPath) {
		case RF90_PATH_A:
		case RF90_PATH_C:
			rtl8192_setBBreg(dev, pPhyReg->rfintfs, bRFSI_RFENV, u4RegValue);
			break;
		case RF90_PATH_B:
		case RF90_PATH_D:
			rtl8192_setBBreg(dev, pPhyReg->rfintfs, bRFSI_RFENV << 16, u4RegValue);
			break;
		}

		if (ret) {
			RT_TRACE(COMP_ERR, "phy_rf8256_config_para_file():Radio[%d] Fail!!", eRFPath);
			goto phy_RF8256_Config_ParaFile_Fail;
		}
	}

	RT_TRACE(COMP_PHY, "PHY Initialization Success\n");
	return;

phy_RF8256_Config_ParaFile_Fail:
	RT_TRACE(COMP_ERR, "PHY Initialization failed\n");
}