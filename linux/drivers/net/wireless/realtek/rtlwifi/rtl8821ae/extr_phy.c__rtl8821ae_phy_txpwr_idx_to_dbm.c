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
typedef  int u8 ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */
#define  WIRELESS_MODE_B 130 
#define  WIRELESS_MODE_G 129 
#define  WIRELESS_MODE_N_24G 128 

__attribute__((used)) static long _rtl8821ae_phy_txpwr_idx_to_dbm(struct ieee80211_hw *hw,
					    enum wireless_mode wirelessmode,
					    u8 txpwridx)
{
	long offset;
	long pwrout_dbm;

	switch (wirelessmode) {
	case WIRELESS_MODE_B:
		offset = -7;
		break;
	case WIRELESS_MODE_G:
	case WIRELESS_MODE_N_24G:
		offset = -8;
		break;
	default:
		offset = -8;
		break;
	}
	pwrout_dbm = txpwridx / 2 + offset;
	return pwrout_dbm;
}