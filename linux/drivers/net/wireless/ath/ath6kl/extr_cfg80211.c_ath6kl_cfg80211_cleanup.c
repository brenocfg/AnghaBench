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
struct ath6kl {int wiphy_registered; int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wiphy_unregister (int /*<<< orphan*/ ) ; 

void ath6kl_cfg80211_cleanup(struct ath6kl *ar)
{
	wiphy_unregister(ar->wiphy);

	ar->wiphy_registered = false;
}