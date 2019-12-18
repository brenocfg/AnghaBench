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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_NORMAL_CHIP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl92cu_init_chipn_queue_priority (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl92cu_init_chipt_queue_priority (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92cu_init_queue_priority(struct ieee80211_hw *hw,
						bool wmm_enable,
						u8 out_ep_num,
						u8 queue_sel)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (IS_NORMAL_CHIP(rtlhal->version))
		_rtl92cu_init_chipn_queue_priority(hw, wmm_enable, out_ep_num,
						   queue_sel);
	else
		_rtl92cu_init_chipt_queue_priority(hw, wmm_enable, out_ep_num,
						   queue_sel);
}