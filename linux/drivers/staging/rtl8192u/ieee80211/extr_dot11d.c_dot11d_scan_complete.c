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
struct rt_dot11d_info {int state; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
#define  DOT11D_STATE_DONE 130 
#define  DOT11D_STATE_LEARNED 129 
#define  DOT11D_STATE_NONE 128 
 int /*<<< orphan*/  GET_CIE_WATCHDOG (struct ieee80211_device*) ; 
 struct rt_dot11d_info* GET_DOT11D_INFO (struct ieee80211_device*) ; 
 int /*<<< orphan*/  dot11d_reset (struct ieee80211_device*) ; 

void dot11d_scan_complete(struct ieee80211_device *dev)
{
	struct rt_dot11d_info *dot11d_info = GET_DOT11D_INFO(dev);

	switch (dot11d_info->state) {
	case DOT11D_STATE_LEARNED:
		dot11d_info->state = DOT11D_STATE_DONE;
		break;

	case DOT11D_STATE_DONE:
		if (GET_CIE_WATCHDOG(dev) == 0) {
			/* Reset country IE if previous one is gone. */
			dot11d_reset(dev);
		}
		break;
	case DOT11D_STATE_NONE:
		break;
	}
}