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
 int MASKDWORD ; 
 int MASKLWORD ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 

__attribute__((used)) static void _rtl8812ae_bb8812_config_1t(struct ieee80211_hw *hw)
{
	/* BB OFDM RX Path_A */
	rtl_set_bbreg(hw, 0x808, 0xff, 0x11);
	/* BB OFDM TX Path_A */
	rtl_set_bbreg(hw, 0x80c, MASKLWORD, 0x1111);
	/* BB CCK R/Rx Path_A */
	rtl_set_bbreg(hw, 0xa04, 0x0c000000, 0x0);
	/* MCS support */
	rtl_set_bbreg(hw, 0x8bc, 0xc0000060, 0x4);
	/* RF Path_B HSSI OFF */
	rtl_set_bbreg(hw, 0xe00, 0xf, 0x4);
	/* RF Path_B Power Down */
	rtl_set_bbreg(hw, 0xe90, MASKDWORD, 0);
	/* ADDA Path_B OFF */
	rtl_set_bbreg(hw, 0xe60, MASKDWORD, 0);
	rtl_set_bbreg(hw, 0xe64, MASKDWORD, 0);
}