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
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void rs_rate_init_stub(void *priv_r, struct ieee80211_supported_band *sband,
			      struct cfg80211_chan_def *chandef,
			      struct ieee80211_sta *sta, void *priv_sta)
{
}