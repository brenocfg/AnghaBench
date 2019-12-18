#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ iftype; } ;
struct brcmf_cfg80211_vif {TYPE_1__ wdev; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_ADHOC ; 

__attribute__((used)) static bool brcmf_is_ibssmode(struct brcmf_cfg80211_vif *vif)
{
	return vif->wdev.iftype == NL80211_IFTYPE_ADHOC;
}