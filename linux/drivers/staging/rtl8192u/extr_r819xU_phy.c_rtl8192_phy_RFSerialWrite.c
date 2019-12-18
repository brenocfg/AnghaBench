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
struct TYPE_2__ {int /*<<< orphan*/  rf3wireOffset; } ;
typedef  TYPE_1__ BB_REGISTER_DEFINITION_T ;

/* Variables and functions */
 int COMP_ERR ; 
 int COMP_PHY ; 
 scalar_t__ RF_8256 ; 
 int /*<<< orphan*/  RT_TRACE (int,char*) ; 
 int /*<<< orphan*/  bMaskDWord ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8192_phy_RFSerialWrite(struct net_device *dev,
				      enum rf90_radio_path_e e_rfpath,
				      u32 offset,
				      u32 data)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32 DataAndAddr = 0, new_offset = 0;
	BB_REGISTER_DEFINITION_T	*pPhyReg = &priv->PHYRegDef[e_rfpath];

	offset &= 0x3f;
	if (priv->rf_chip == RF_8256) {

		if (offset >= 31) {
			priv->RfReg0Value[e_rfpath] |= 0x140;
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset,
					 bMaskDWord,
					 priv->RfReg0Value[e_rfpath] << 16);
			new_offset = offset - 30;
		} else if (offset >= 16) {
			priv->RfReg0Value[e_rfpath] |= 0x100;
			priv->RfReg0Value[e_rfpath] &= (~0x40);
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

	/* Put write addr in [5:0] and write data in [31:16] */
	DataAndAddr = (data<<16) | (new_offset&0x3f);

	/* Write operation */
	rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset, bMaskDWord, DataAndAddr);


	if (offset == 0x0)
		priv->RfReg0Value[e_rfpath] = data;

	/* Switch back to Reg_Mode0 */
	if (priv->rf_chip == RF_8256) {
		if (offset != 0) {
			priv->RfReg0Value[e_rfpath] &= 0xebf;
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset,
					 bMaskDWord,
					 priv->RfReg0Value[e_rfpath] << 16);
		}
	}
}