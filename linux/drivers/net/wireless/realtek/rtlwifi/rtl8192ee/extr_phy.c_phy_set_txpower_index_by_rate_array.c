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
typedef  size_t u8 ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 size_t _rtl92ee_get_txpower_index (struct ieee80211_hw*,int,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  _rtl92ee_set_txpower_index (struct ieee80211_hw*,size_t,int,size_t) ; 

__attribute__((used)) static void phy_set_txpower_index_by_rate_array(struct ieee80211_hw *hw,
						enum radio_path rfpath, u8 bw,
						u8 channel, u8 *rates, u8 size)
{
	u8 i;
	u8 power_index;

	for (i = 0; i < size; i++) {
		power_index = _rtl92ee_get_txpower_index(hw, rfpath, rates[i],
							 bw, channel);
		_rtl92ee_set_txpower_index(hw, power_index, rfpath, rates[i]);
	}
}