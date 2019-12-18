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
struct rt_dot11d_info {size_t* max_tx_pwr_dbm_list; scalar_t__* channel_map; } ;
struct ieee80211_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rt_dot11d_info* GET_DOT11D_INFO (struct ieee80211_device*) ; 
 size_t MAX_CHANNEL_NUMBER ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

u8 dot11d_get_max_tx_pwr_in_dbm(struct ieee80211_device *dev, u8 Channel)
{
	struct rt_dot11d_info *dot11d_info = GET_DOT11D_INFO(dev);
	u8 MaxTxPwrInDbm = 255;

	if (Channel > MAX_CHANNEL_NUMBER) {
		netdev_err(dev->dev, "dot11d_get_max_tx_pwr_in_dbm(): Invalid Channel\n");
		return MaxTxPwrInDbm;
	}
	if (dot11d_info->channel_map[Channel])
		MaxTxPwrInDbm = dot11d_info->max_tx_pwr_dbm_list[Channel];

	return MaxTxPwrInDbm;
}