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
struct lbs_private {int /*<<< orphan*/ * scan_req; scalar_t__ internal_scan; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_scan_done (int /*<<< orphan*/ *,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void lbs_scan_done(struct lbs_private *priv)
{
	WARN_ON(!priv->scan_req);

	if (priv->internal_scan) {
		kfree(priv->scan_req);
	} else {
		struct cfg80211_scan_info info = {
			.aborted = false,
		};

		cfg80211_scan_done(priv->scan_req, &info);
	}

	priv->scan_req = NULL;
}