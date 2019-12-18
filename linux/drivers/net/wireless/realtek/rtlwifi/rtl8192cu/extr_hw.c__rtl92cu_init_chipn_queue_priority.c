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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _rtl92cu_init_chipn_one_out_ep_priority (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  _rtl92cu_init_chipn_three_out_ep_priority (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  _rtl92cu_init_chipn_two_out_ep_priority (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static void _rtl92cu_init_chipn_queue_priority(struct ieee80211_hw *hw,
					       bool wmm_enable,
					       u8 out_ep_num,
					       u8 queue_sel)
{
	switch (out_ep_num) {
	case 1:
		_rtl92cu_init_chipn_one_out_ep_priority(hw, wmm_enable,
							queue_sel);
		break;
	case 2:
		_rtl92cu_init_chipn_two_out_ep_priority(hw, wmm_enable,
							queue_sel);
		break;
	case 3:
		_rtl92cu_init_chipn_three_out_ep_priority(hw, wmm_enable,
							  queue_sel);
		break;
	default:
		WARN_ON(1); /* Shall not reach here! */
		break;
	}
}