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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct rate_adaptive {scalar_t__ high_rssi_thresh_for_ra; scalar_t__ low_rssi_thresh_for_ra40m; } ;
struct rtl_priv {struct rate_adaptive ra; } ;
struct ieee80211_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RATR ; 
 int /*<<< orphan*/  DBG_DMESG ; 
#define  DM_RATR_STA_HIGH 131 
#define  DM_RATR_STA_INIT 130 
#define  DM_RATR_STA_LOW 129 
#define  DM_RATR_STA_MIDDLE 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool _rtl92ee_dm_ra_state_check(struct ieee80211_hw *hw,
				       s32 rssi, u8 *ratr_state)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rate_adaptive *p_ra = &rtlpriv->ra;
	const u8 go_up_gap = 5;
	u32 high_rssithresh_for_ra = p_ra->high_rssi_thresh_for_ra;
	u32 low_rssithresh_for_ra = p_ra->low_rssi_thresh_for_ra40m;
	u8 state;

	/* Threshold Adjustment:
	 * when RSSI state trends to go up one or two levels,
	 * make sure RSSI is high enough.
	 * Here GoUpGap is added to solve
	 * the boundary's level alternation issue.
	 */
	switch (*ratr_state) {
	case DM_RATR_STA_INIT:
	case DM_RATR_STA_HIGH:
		break;
	case DM_RATR_STA_MIDDLE:
		high_rssithresh_for_ra += go_up_gap;
		break;
	case DM_RATR_STA_LOW:
		high_rssithresh_for_ra += go_up_gap;
		low_rssithresh_for_ra += go_up_gap;
		break;
	default:
		RT_TRACE(rtlpriv, COMP_RATR, DBG_DMESG,
			 "wrong rssi level setting %d !\n", *ratr_state);
		break;
	}

	/* Decide RATRState by RSSI. */
	if (rssi > high_rssithresh_for_ra)
		state = DM_RATR_STA_HIGH;
	else if (rssi > low_rssithresh_for_ra)
		state = DM_RATR_STA_MIDDLE;
	else
		state = DM_RATR_STA_LOW;

	if (*ratr_state != state) {
		*ratr_state = state;
		return true;
	}

	return false;
}