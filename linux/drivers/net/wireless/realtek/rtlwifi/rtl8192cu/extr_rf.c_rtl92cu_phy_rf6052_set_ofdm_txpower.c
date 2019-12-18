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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl92c_get_txpower_writeval_by_regulatory (struct ieee80211_hw*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtl92c_write_ofdm_power_reg (struct ieee80211_hw*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl92c_phy_get_power_base (struct ieee80211_hw*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rtl92cu_phy_rf6052_set_ofdm_txpower(struct ieee80211_hw *hw,
					 u8 *ppowerlevel, u8 channel)
{
	u32 writeval[2], powerbase0[2], powerbase1[2];
	u8 index = 0;

	rtl92c_phy_get_power_base(hw, ppowerlevel,
				  channel, &powerbase0[0], &powerbase1[0]);
	for (index = 0; index < 6; index++) {
		_rtl92c_get_txpower_writeval_by_regulatory(hw,
							   channel, index,
							   &powerbase0[0],
							   &powerbase1[0],
							   &writeval[0]);
		_rtl92c_write_ofdm_power_reg(hw, index, &writeval[0]);
	}
}