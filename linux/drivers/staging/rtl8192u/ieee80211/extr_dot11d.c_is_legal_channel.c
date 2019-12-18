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
struct rt_dot11d_info {scalar_t__* channel_map; } ;
struct ieee80211_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rt_dot11d_info* GET_DOT11D_INFO (struct ieee80211_device*) ; 
 size_t MAX_CHANNEL_NUMBER ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

int is_legal_channel(struct ieee80211_device *dev, u8 channel)
{
	struct rt_dot11d_info *dot11d_info = GET_DOT11D_INFO(dev);

	if (channel > MAX_CHANNEL_NUMBER) {
		netdev_err(dev->dev, "is_legal_channel(): Invalid Channel\n");
		return 0;
	}
	if (dot11d_info->channel_map[channel] > 0)
		return 1;
	return 0;
}