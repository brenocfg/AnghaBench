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
struct rtl_phy {TYPE_1__* phyreg_def; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rf_rbpi; int /*<<< orphan*/  rf_rb; void* rfhssi_para2; int /*<<< orphan*/  rf3wire_offset; void* rfintfe; void* rfintfo; void* rfintfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  RA_LSSIWRITE_8821A ; 
 int /*<<< orphan*/  RA_PIREAD_8821A ; 
 int /*<<< orphan*/  RA_SIREAD_8821A ; 
 int /*<<< orphan*/  RB_LSSIWRITE_8821A ; 
 int /*<<< orphan*/  RB_PIREAD_8821A ; 
 int /*<<< orphan*/  RB_SIREAD_8821A ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_B ; 
 void* RFPGA0_XAB_RFINTERFACESW ; 
 void* RFPGA0_XA_RFINTERFACEOE ; 
 void* RFPGA0_XB_RFINTERFACEOE ; 
 void* RHSSIREAD_8821AE ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void phy_init_bb_rf_register_definition(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	rtlphy->phyreg_def[RF90_PATH_A].rfintfs = RFPGA0_XAB_RFINTERFACESW;
	rtlphy->phyreg_def[RF90_PATH_B].rfintfs = RFPGA0_XAB_RFINTERFACESW;

	rtlphy->phyreg_def[RF90_PATH_A].rfintfo = RFPGA0_XA_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_B].rfintfo = RFPGA0_XB_RFINTERFACEOE;

	rtlphy->phyreg_def[RF90_PATH_A].rfintfe = RFPGA0_XA_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_B].rfintfe = RFPGA0_XB_RFINTERFACEOE;

	rtlphy->phyreg_def[RF90_PATH_A].rf3wire_offset = RA_LSSIWRITE_8821A;
	rtlphy->phyreg_def[RF90_PATH_B].rf3wire_offset = RB_LSSIWRITE_8821A;

	rtlphy->phyreg_def[RF90_PATH_A].rfhssi_para2 = RHSSIREAD_8821AE;
	rtlphy->phyreg_def[RF90_PATH_B].rfhssi_para2 = RHSSIREAD_8821AE;

	rtlphy->phyreg_def[RF90_PATH_A].rf_rb = RA_SIREAD_8821A;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rb = RB_SIREAD_8821A;

	rtlphy->phyreg_def[RF90_PATH_A].rf_rbpi = RA_PIREAD_8821A;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rbpi = RB_PIREAD_8821A;
}