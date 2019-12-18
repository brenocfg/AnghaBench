#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_8__ {int width; TYPE_1__* chan; } ;
struct TYPE_9__ {TYPE_2__ chandef; } ;
struct mt7615_dev {int dfs_state; TYPE_3__ mt76; } ;
struct TYPE_10__ {int width; TYPE_5__* chan; } ;
struct TYPE_12__ {TYPE_4__ chandef; } ;
struct ieee80211_hw {TYPE_6__ conf; } ;
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;
struct TYPE_11__ {scalar_t__ center_freq; } ;
struct TYPE_7__ {scalar_t__ center_freq; } ;

/* Variables and functions */
 struct ieee80211_hw* mt76_hw (struct mt7615_dev*) ; 

__attribute__((used)) static inline void mt7615_dfs_check_channel(struct mt7615_dev *dev)
{
	enum nl80211_chan_width width = dev->mt76.chandef.width;
	u32 freq = dev->mt76.chandef.chan->center_freq;
	struct ieee80211_hw *hw = mt76_hw(dev);

	if (hw->conf.chandef.chan->center_freq != freq ||
	    hw->conf.chandef.width != width)
		dev->dfs_state = -1;
}