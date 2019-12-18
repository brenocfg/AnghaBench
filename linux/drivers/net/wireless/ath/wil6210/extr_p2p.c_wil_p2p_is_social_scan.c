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
struct cfg80211_scan_request {int n_channels; TYPE_1__** channels; } ;
struct TYPE_2__ {scalar_t__ hw_value; } ;

/* Variables and functions */
 scalar_t__ P2P_DMG_SOCIAL_CHANNEL ; 

bool wil_p2p_is_social_scan(struct cfg80211_scan_request *request)
{
	return (request->n_channels == 1) &&
	       (request->channels[0]->hw_value == P2P_DMG_SOCIAL_CHANNEL);
}