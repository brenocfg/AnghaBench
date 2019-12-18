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
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92ee_dm_dynamic_arfb_select (struct ieee80211_hw*,int,int) ; 

void rtl92ee_c2h_ra_report_handler(struct ieee80211_hw *hw,
				   u8 *cmd_buf, u8 cmd_len)
{
	u8 rate = cmd_buf[0] & 0x3F;
	bool collision_state = cmd_buf[3] & BIT(0);

	rtl92ee_dm_dynamic_arfb_select(hw, rate, collision_state);
}