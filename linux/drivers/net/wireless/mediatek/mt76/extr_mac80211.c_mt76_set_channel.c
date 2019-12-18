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
struct cfg80211_chan_def {int /*<<< orphan*/  chan; } ;
struct mt76_dev {int /*<<< orphan*/  main_chan; struct cfg80211_chan_def chandef; TYPE_2__* drv; int /*<<< orphan*/  tx_wait; struct ieee80211_hw* hw; } ;
struct mt76_channel_state {int dummy; } ;
struct TYPE_3__ {int flags; struct cfg80211_chan_def chandef; } ;
struct ieee80211_hw {TYPE_1__ conf; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* update_survey ) (struct mt76_dev*) ;} ;

/* Variables and functions */
 int HZ ; 
 int IEEE80211_CONF_OFFCHANNEL ; 
 int /*<<< orphan*/  memset (struct mt76_channel_state*,int /*<<< orphan*/ ,int) ; 
 struct mt76_channel_state* mt76_channel_state (struct mt76_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_has_tx_pending (struct mt76_dev*) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

void mt76_set_channel(struct mt76_dev *dev)
{
	struct ieee80211_hw *hw = dev->hw;
	struct cfg80211_chan_def *chandef = &hw->conf.chandef;
	struct mt76_channel_state *state;
	bool offchannel = hw->conf.flags & IEEE80211_CONF_OFFCHANNEL;
	int timeout = HZ / 5;

	wait_event_timeout(dev->tx_wait, !mt76_has_tx_pending(dev), timeout);

	if (dev->drv->update_survey)
		dev->drv->update_survey(dev);

	dev->chandef = *chandef;

	if (!offchannel)
		dev->main_chan = chandef->chan;

	if (chandef->chan != dev->main_chan) {
		state = mt76_channel_state(dev, chandef->chan);
		memset(state, 0, sizeof(*state));
	}
}