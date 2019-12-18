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
struct r8192_priv {scalar_t__ Rf_Mode; } ;
struct net_device {int dummy; } ;
typedef  enum rf90_radio_path_e { ____Placeholder_rf90_radio_path_e } rf90_radio_path_e ;

/* Variables and functions */
 scalar_t__ RF_OP_By_FW ; 
 int bMask12Bits ; 
 int ffs (int) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int phy_FwRFSerialRead (struct net_device*,int,int) ; 
 int /*<<< orphan*/  phy_FwRFSerialWrite (struct net_device*,int,int,int) ; 
 int /*<<< orphan*/  rtl8192_phy_CheckIsLegalRFPath (struct net_device*,int) ; 
 int rtl8192_phy_RFSerialRead (struct net_device*,int,int) ; 
 int /*<<< orphan*/  rtl8192_phy_RFSerialWrite (struct net_device*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl8192_phy_SetRFReg(struct net_device *dev,
			  enum rf90_radio_path_e e_rfpath,
			  u32 reg_addr, u32 bitmask, u32 data)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32 reg, bitshift;

	if (!rtl8192_phy_CheckIsLegalRFPath(dev, e_rfpath))
		return;

	if (priv->Rf_Mode == RF_OP_By_FW) {
		if (bitmask != bMask12Bits) {
			/* RF data is 12 bits only */
			reg = phy_FwRFSerialRead(dev, e_rfpath, reg_addr);
			bitshift =  ffs(bitmask) - 1;
			reg &= ~bitmask;
			reg |= data << bitshift;

			phy_FwRFSerialWrite(dev, e_rfpath, reg_addr, reg);
		} else {
			phy_FwRFSerialWrite(dev, e_rfpath, reg_addr, data);
		}

		udelay(200);

	} else {
		if (bitmask != bMask12Bits) {
			/* RF data is 12 bits only */
			reg = rtl8192_phy_RFSerialRead(dev, e_rfpath, reg_addr);
			bitshift =  ffs(bitmask) - 1;
			reg &= ~bitmask;
			reg |= data << bitshift;

			rtl8192_phy_RFSerialWrite(dev, e_rfpath, reg_addr, reg);
		} else {
			rtl8192_phy_RFSerialWrite(dev, e_rfpath, reg_addr, data);
		}
	}
}