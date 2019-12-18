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
struct wiphy {int dummy; } ;

/* Variables and functions */
 scalar_t__ wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static void *mwifiex_cfg80211_get_adapter(struct wiphy *wiphy)
{
	return (void *) (*(unsigned long *) wiphy_priv(wiphy));
}