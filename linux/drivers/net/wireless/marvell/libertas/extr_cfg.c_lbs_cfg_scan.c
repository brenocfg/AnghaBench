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
struct lbs_private {scalar_t__ surpriseremoved; int /*<<< orphan*/  scan_work; scalar_t__ scan_req; } ;
struct cfg80211_scan_request {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  _internal_start_scan (struct lbs_private*,int,struct cfg80211_scan_request*) ; 
 scalar_t__ delayed_work_pending (int /*<<< orphan*/ *) ; 
 struct lbs_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int lbs_cfg_scan(struct wiphy *wiphy,
	struct cfg80211_scan_request *request)
{
	struct lbs_private *priv = wiphy_priv(wiphy);
	int ret = 0;

	if (priv->scan_req || delayed_work_pending(&priv->scan_work)) {
		/* old scan request not yet processed */
		ret = -EAGAIN;
		goto out;
	}

	_internal_start_scan(priv, false, request);

	if (priv->surpriseremoved)
		ret = -EIO;

 out:
	return ret;
}