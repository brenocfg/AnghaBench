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
struct rt_dot11d_info {int dot11d_enabled; int /*<<< orphan*/  max_tx_pwr_dbm_list; int /*<<< orphan*/  channel_map; scalar_t__ country_ie_len; int /*<<< orphan*/  state; } ;
struct ieee80211_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11D_STATE_NONE ; 
 struct rt_dot11d_info* GET_DOT11D_INFO (struct ieee80211_device*) ; 
 scalar_t__ MAX_CHANNEL_NUMBER ; 
 int /*<<< orphan*/  RESET_CIE_WATCHDOG (struct ieee80211_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 

void rtl8192u_dot11d_init(struct ieee80211_device *ieee)
{
	struct rt_dot11d_info *dot11d_info = GET_DOT11D_INFO(ieee);

	dot11d_info->dot11d_enabled = false;

	dot11d_info->state = DOT11D_STATE_NONE;
	dot11d_info->country_ie_len = 0;
	memset(dot11d_info->channel_map, 0, MAX_CHANNEL_NUMBER + 1);
	memset(dot11d_info->max_tx_pwr_dbm_list, 0xFF, MAX_CHANNEL_NUMBER + 1);
	RESET_CIE_WATCHDOG(ieee);

	netdev_info(ieee->dev, "rtl8192u_dot11d_init()\n");
}