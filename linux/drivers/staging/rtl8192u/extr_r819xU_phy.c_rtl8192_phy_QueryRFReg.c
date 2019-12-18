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
 int ffs (int) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int phy_FwRFSerialRead (struct net_device*,int,int) ; 
 int /*<<< orphan*/  rtl8192_phy_CheckIsLegalRFPath (struct net_device*,int) ; 
 int rtl8192_phy_RFSerialRead (struct net_device*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

u32 rtl8192_phy_QueryRFReg(struct net_device *dev,
			   enum rf90_radio_path_e e_rfpath,
			   u32 reg_addr, u32 bitmask)
{
	u32 reg, bitshift;
	struct r8192_priv *priv = ieee80211_priv(dev);


	if (!rtl8192_phy_CheckIsLegalRFPath(dev, e_rfpath))
		return 0;
	if (priv->Rf_Mode == RF_OP_By_FW) {
		reg = phy_FwRFSerialRead(dev, e_rfpath, reg_addr);
		udelay(200);
	} else {
		reg = rtl8192_phy_RFSerialRead(dev, e_rfpath, reg_addr);
	}
	bitshift =  ffs(bitmask) - 1;
	reg = (reg & bitmask) >> bitshift;
	return reg;

}