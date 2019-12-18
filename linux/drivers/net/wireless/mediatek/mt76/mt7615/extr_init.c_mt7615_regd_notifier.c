#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int dummy; } ;
struct regulatory_request {scalar_t__ dfs_region; } ;
struct cfg80211_chan_def {TYPE_1__* chan; } ;
struct TYPE_4__ {scalar_t__ region; struct cfg80211_chan_def chandef; } ;
struct mt7615_dev {TYPE_2__ mt76; } ;
struct ieee80211_hw {struct mt7615_dev* priv; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  MT_HW_RDD0 ; 
 int /*<<< orphan*/  MT_RX_SEL0 ; 
 scalar_t__ NL80211_DFS_UNSET ; 
 int /*<<< orphan*/  RDD_CAC_END ; 
 int /*<<< orphan*/  mt7615_dfs_start_radar_detector (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt7615_dfs_stop_radar_detector (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt7615_mcu_rdd_cmd (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* wiphy_to_ieee80211_hw (struct wiphy*) ; 

__attribute__((used)) static void
mt7615_regd_notifier(struct wiphy *wiphy,
		     struct regulatory_request *request)
{
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct mt7615_dev *dev = hw->priv;
	struct cfg80211_chan_def *chandef = &dev->mt76.chandef;

	if (request->dfs_region == dev->mt76.region)
		return;

	dev->mt76.region = request->dfs_region;

	if (!(chandef->chan->flags & IEEE80211_CHAN_RADAR))
		return;

	mt7615_dfs_stop_radar_detector(dev);
	if (request->dfs_region == NL80211_DFS_UNSET)
		mt7615_mcu_rdd_cmd(dev, RDD_CAC_END, MT_HW_RDD0,
				   MT_RX_SEL0, 0);
	else
		mt7615_dfs_start_radar_detector(dev);
}