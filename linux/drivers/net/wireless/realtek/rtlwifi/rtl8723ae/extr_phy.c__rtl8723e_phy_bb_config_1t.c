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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int MASKBYTE0 ; 
 int MASKBYTE3 ; 
 int RCCK0_AFESETTING ; 
 int RFPGA0_TXINFO ; 
 int RFPGA1_TXINFO ; 
 int ROFDM0_AGCPARAMETER1 ; 
 int ROFDM0_TRXPATHENABLE ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 

__attribute__((used)) static void _rtl8723e_phy_bb_config_1t(struct ieee80211_hw *hw)
{
	rtl_set_bbreg(hw, RFPGA0_TXINFO, 0x3, 0x2);
	rtl_set_bbreg(hw, RFPGA1_TXINFO, 0x300033, 0x200022);
	rtl_set_bbreg(hw, RCCK0_AFESETTING, MASKBYTE3, 0x45);
	rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE, MASKBYTE0, 0x23);
	rtl_set_bbreg(hw, ROFDM0_AGCPARAMETER1, 0x30, 0x1);
	rtl_set_bbreg(hw, 0xe74, 0x0c000000, 0x2);
	rtl_set_bbreg(hw, 0xe78, 0x0c000000, 0x2);
	rtl_set_bbreg(hw, 0xe7c, 0x0c000000, 0x2);
	rtl_set_bbreg(hw, 0xe80, 0x0c000000, 0x2);
	rtl_set_bbreg(hw, 0xe88, 0x0c000000, 0x2);
}