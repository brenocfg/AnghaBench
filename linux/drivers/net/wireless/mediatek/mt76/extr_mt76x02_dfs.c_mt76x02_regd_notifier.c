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
struct regulatory_request {int /*<<< orphan*/  dfs_region; } ;
struct mt76x02_dev {int dummy; } ;
struct ieee80211_hw {struct mt76x02_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x02_dfs_set_domain (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* wiphy_to_ieee80211_hw (struct wiphy*) ; 

void mt76x02_regd_notifier(struct wiphy *wiphy,
			   struct regulatory_request *request)
{
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct mt76x02_dev *dev = hw->priv;

	mt76x02_dfs_set_domain(dev, request->dfs_region);
}