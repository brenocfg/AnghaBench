#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {scalar_t__ monitor_type; struct net_device* ddev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE80211 ; 
 int /*<<< orphan*/  ARPHRD_IEEE80211_PRISM ; 
 int /*<<< orphan*/  ARPHRD_IEEE80211_RADIOTAP ; 
 scalar_t__ PRISM2_MONITOR_CAPHDR ; 
 scalar_t__ PRISM2_MONITOR_PRISM ; 
 scalar_t__ PRISM2_MONITOR_RADIOTAP ; 

__attribute__((used)) static void hostap_monitor_set_type(local_info_t *local)
{
	struct net_device *dev = local->ddev;

	if (dev == NULL)
		return;

	if (local->monitor_type == PRISM2_MONITOR_PRISM ||
	    local->monitor_type == PRISM2_MONITOR_CAPHDR) {
		dev->type = ARPHRD_IEEE80211_PRISM;
	} else if (local->monitor_type == PRISM2_MONITOR_RADIOTAP) {
		dev->type = ARPHRD_IEEE80211_RADIOTAP;
	} else {
		dev->type = ARPHRD_IEEE80211;
	}
}