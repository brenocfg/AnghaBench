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
struct survey_info {int filled; void* time_busy; void* time; struct ieee80211_channel* channel; } ;
struct TYPE_4__ {int n_channels; struct ieee80211_channel* channels; } ;
struct mt76_sband {TYPE_2__ sband; } ;
struct mt76_dev {int /*<<< orphan*/  cc_lock; struct ieee80211_channel* main_chan; struct mt76_sband sband_5g; struct mt76_sband sband_2g; TYPE_1__* drv; } ;
struct mt76_channel_state {int /*<<< orphan*/  cc_busy; int /*<<< orphan*/  cc_active; } ;
struct ieee80211_hw {struct mt76_dev* priv; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_survey ) (struct mt76_dev*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int SURVEY_INFO_IN_USE ; 
 int SURVEY_INFO_TIME ; 
 int SURVEY_INFO_TIME_BUSY ; 
 void* div_u64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct survey_info*,int /*<<< orphan*/ ,int) ; 
 struct mt76_channel_state* mt76_channel_state (struct mt76_dev*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*) ; 

int mt76_get_survey(struct ieee80211_hw *hw, int idx,
		    struct survey_info *survey)
{
	struct mt76_dev *dev = hw->priv;
	struct mt76_sband *sband;
	struct ieee80211_channel *chan;
	struct mt76_channel_state *state;
	int ret = 0;

	if (idx == 0 && dev->drv->update_survey)
		dev->drv->update_survey(dev);

	sband = &dev->sband_2g;
	if (idx >= sband->sband.n_channels) {
		idx -= sband->sband.n_channels;
		sband = &dev->sband_5g;
	}

	if (idx >= sband->sband.n_channels)
		return -ENOENT;

	chan = &sband->sband.channels[idx];
	state = mt76_channel_state(dev, chan);

	memset(survey, 0, sizeof(*survey));
	survey->channel = chan;
	survey->filled = SURVEY_INFO_TIME | SURVEY_INFO_TIME_BUSY;
	if (chan == dev->main_chan)
		survey->filled |= SURVEY_INFO_IN_USE;

	spin_lock_bh(&dev->cc_lock);
	survey->time = div_u64(state->cc_active, 1000);
	survey->time_busy = div_u64(state->cc_busy, 1000);
	spin_unlock_bh(&dev->cc_lock);

	return ret;
}