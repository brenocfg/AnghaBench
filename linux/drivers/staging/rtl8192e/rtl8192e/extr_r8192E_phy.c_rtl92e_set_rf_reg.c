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
struct r8192_priv {scalar_t__ Rf_Mode; int /*<<< orphan*/  being_init_adapter; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
typedef  enum rf90_radio_path { ____Placeholder_rf90_radio_path } rf90_radio_path ;
struct TYPE_2__ {scalar_t__ eRFPowerState; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_PHY ; 
 scalar_t__ RF_OP_By_FW ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int _rtl92e_calculate_bit_shift (int) ; 
 int _rtl92e_phy_rf_fw_read (struct net_device*,int,int) ; 
 int /*<<< orphan*/  _rtl92e_phy_rf_fw_write (struct net_device*,int,int,int) ; 
 int _rtl92e_phy_rf_read (struct net_device*,int,int) ; 
 int /*<<< orphan*/  _rtl92e_phy_rf_write (struct net_device*,int,int,int) ; 
 int bMask12Bits ; 
 scalar_t__ eRfOn ; 
 int /*<<< orphan*/  rtl92e_is_legal_rf_path (struct net_device*,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl92e_set_rf_reg(struct net_device *dev, enum rf90_radio_path eRFPath,
		       u32 RegAddr, u32 BitMask, u32 Data)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	u32 Original_Value, BitShift, New_Value;

	if (!rtl92e_is_legal_rf_path(dev, eRFPath))
		return;
	if (priv->rtllib->eRFPowerState != eRfOn && !priv->being_init_adapter)
		return;

	RT_TRACE(COMP_PHY, "FW RF CTRL is not ready now\n");
	if (priv->Rf_Mode == RF_OP_By_FW) {
		if (BitMask != bMask12Bits) {
			Original_Value = _rtl92e_phy_rf_fw_read(dev, eRFPath,
								RegAddr);
			BitShift =  _rtl92e_calculate_bit_shift(BitMask);
			New_Value = (Original_Value & ~BitMask) | (Data << BitShift);

			_rtl92e_phy_rf_fw_write(dev, eRFPath, RegAddr,
						New_Value);
		} else
			_rtl92e_phy_rf_fw_write(dev, eRFPath, RegAddr, Data);
		udelay(200);

	} else {
		if (BitMask != bMask12Bits) {
			Original_Value = _rtl92e_phy_rf_read(dev, eRFPath,
							     RegAddr);
			BitShift =  _rtl92e_calculate_bit_shift(BitMask);
			New_Value = (Original_Value & ~BitMask) | (Data << BitShift);

			_rtl92e_phy_rf_write(dev, eRFPath, RegAddr, New_Value);
		} else
			_rtl92e_phy_rf_write(dev, eRFPath, RegAddr, Data);
	}
}