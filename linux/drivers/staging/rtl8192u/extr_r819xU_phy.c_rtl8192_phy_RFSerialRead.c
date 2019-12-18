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
typedef  int u32 ;
struct r8192_priv {scalar_t__ rf_chip; int* RfReg0Value; TYPE_1__* PHYRegDef; } ;
struct net_device {int dummy; } ;
typedef  enum rf90_radio_path_e { ____Placeholder_rf90_radio_path_e } rf90_radio_path_e ;
struct TYPE_2__ {int /*<<< orphan*/  rf3wireOffset; int /*<<< orphan*/  rfLSSIReadBack; int /*<<< orphan*/  rfHSSIPara2; } ;
typedef  TYPE_1__ BB_REGISTER_DEFINITION_T ;

/* Variables and functions */
 int COMP_ERR ; 
 int COMP_PHY ; 
 scalar_t__ RF_8256 ; 
 int /*<<< orphan*/  RT_TRACE (int,char*) ; 
 int /*<<< orphan*/  bLSSIReadAddress ; 
 int /*<<< orphan*/  bLSSIReadBackData ; 
 int /*<<< orphan*/  bLSSIReadEdge ; 
 int /*<<< orphan*/  bMaskDWord ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int rtl8192_QueryBBReg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static u32 rtl8192_phy_RFSerialRead(struct net_device *dev,
				    enum rf90_radio_path_e e_rfpath, u32 offset)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32 ret = 0;
	u32 new_offset = 0;
	BB_REGISTER_DEFINITION_T *pPhyReg = &priv->PHYRegDef[e_rfpath];

	rtl8192_setBBreg(dev, pPhyReg->rfLSSIReadBack, bLSSIReadBackData, 0);
	/* Make sure RF register offset is correct */
	offset &= 0x3f;

	/* Switch page for 8256 RF IC */
	if (priv->rf_chip == RF_8256) {
		if (offset >= 31) {
			priv->RfReg0Value[e_rfpath] |= 0x140;
			/* Switch to Reg_Mode2 for Reg 31-45 */
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset,
					 bMaskDWord,
					 priv->RfReg0Value[e_rfpath]<<16);
			/* Modify offset */
			new_offset = offset - 30;
		} else if (offset >= 16) {
			priv->RfReg0Value[e_rfpath] |= 0x100;
			priv->RfReg0Value[e_rfpath] &= (~0x40);
			/* Switch to Reg_Mode1 for Reg16-30 */
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset,
					 bMaskDWord,
					 priv->RfReg0Value[e_rfpath]<<16);

			new_offset = offset - 15;
		} else {
			new_offset = offset;
		}
	} else {
		RT_TRACE((COMP_PHY|COMP_ERR),
			 "check RF type here, need to be 8256\n");
		new_offset = offset;
	}
	/* Put desired read addr to LSSI control Register */
	rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2, bLSSIReadAddress,
			 new_offset);
	/* Issue a posedge trigger */
	rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2,  bLSSIReadEdge, 0x0);
	rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2,  bLSSIReadEdge, 0x1);


	/* TODO: we should not delay such a long time. Ask for help from SD3 */
	usleep_range(1000, 1000);

	ret = rtl8192_QueryBBReg(dev, pPhyReg->rfLSSIReadBack,
				 bLSSIReadBackData);


	/* Switch back to Reg_Mode0 */
	if (priv->rf_chip == RF_8256) {
		priv->RfReg0Value[e_rfpath] &= 0xebf;

		rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset, bMaskDWord,
				 priv->RfReg0Value[e_rfpath] << 16);
	}

	return ret;
}