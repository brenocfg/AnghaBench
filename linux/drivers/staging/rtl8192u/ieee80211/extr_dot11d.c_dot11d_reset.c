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
typedef  int u32 ;
struct rt_dot11d_info {int* channel_map; int* max_tx_pwr_dbm_list; scalar_t__ country_ie_len; int /*<<< orphan*/  state; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11D_STATE_NONE ; 
 struct rt_dot11d_info* GET_DOT11D_INFO (struct ieee80211_device*) ; 
 scalar_t__ MAX_CHANNEL_NUMBER ; 
 int /*<<< orphan*/  RESET_CIE_WATCHDOG (struct ieee80211_device*) ; 
 int /*<<< orphan*/  memset (int*,int,scalar_t__) ; 

void dot11d_reset(struct ieee80211_device *ieee)
{
	u32 i;
	struct rt_dot11d_info *dot11d_info = GET_DOT11D_INFO(ieee);
	/* Clear old channel map */
	memset(dot11d_info->channel_map, 0, MAX_CHANNEL_NUMBER + 1);
	memset(dot11d_info->max_tx_pwr_dbm_list, 0xFF, MAX_CHANNEL_NUMBER + 1);
	/* Set new channel map */
	for (i = 1; i <= 11; i++)
		(dot11d_info->channel_map)[i] = 1;

	for (i = 12; i <= 14; i++)
		(dot11d_info->channel_map)[i] = 2;

	dot11d_info->state = DOT11D_STATE_NONE;
	dot11d_info->country_ie_len = 0;
	RESET_CIE_WATCHDOG(ieee);
}