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
struct wiphy {int dummy; } ;
struct lbs_private {int dummy; } ;
struct cfg80211_chan_def {TYPE_1__* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ NL80211_CHAN_NO_HT ; 
 scalar_t__ cfg80211_get_chandef_type (struct cfg80211_chan_def*) ; 
 int lbs_set_channel (struct lbs_private*,int /*<<< orphan*/ ) ; 
 struct lbs_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int lbs_cfg_set_monitor_channel(struct wiphy *wiphy,
				       struct cfg80211_chan_def *chandef)
{
	struct lbs_private *priv = wiphy_priv(wiphy);
	int ret = -ENOTSUPP;

	if (cfg80211_get_chandef_type(chandef) != NL80211_CHAN_NO_HT)
		goto out;

	ret = lbs_set_channel(priv, chandef->chan->hw_value);

 out:
	return ret;
}