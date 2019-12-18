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
struct survey_info {scalar_t__ time; int /*<<< orphan*/  filled; } ;
struct p54_common {int chan_num; int /*<<< orphan*/ * survey; int /*<<< orphan*/  conf_mutex; struct ieee80211_channel* curchan; } ;
struct ieee80211_hw {struct p54_common* priv; } ;
struct ieee80211_channel {int hw_value; } ;

/* Variables and functions */
 int ENOENT ; 
 int ETIMEDOUT ; 
 int MAX_TRIES ; 
 int /*<<< orphan*/  SURVEY_INFO_IN_USE ; 
 int /*<<< orphan*/  memcpy (struct survey_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int p54_wait_for_stats (struct ieee80211_hw*) ; 

__attribute__((used)) static int p54_get_survey(struct ieee80211_hw *dev, int idx,
				struct survey_info *survey)
{
	struct p54_common *priv = dev->priv;
	struct ieee80211_channel *chan;
	int err, tries;
	bool in_use = false;

	if (idx >= priv->chan_num)
		return -ENOENT;

#define MAX_TRIES 1
	for (tries = 0; tries < MAX_TRIES; tries++) {
		chan = priv->curchan;
		if (chan && chan->hw_value == idx) {
			mutex_lock(&priv->conf_mutex);
			err = p54_wait_for_stats(dev);
			mutex_unlock(&priv->conf_mutex);
			if (err)
				return err;

			in_use = true;
		}

		memcpy(survey, &priv->survey[idx], sizeof(*survey));

		if (in_use) {
			/* test if the reported statistics are valid. */
			if  (survey->time != 0) {
				survey->filled |= SURVEY_INFO_IN_USE;
			} else {
				/*
				 * hw/fw has not accumulated enough sample sets.
				 * Wait for 100ms, this ought to be enough to
				 * to get at least one non-null set of channel
				 * usage statistics.
				 */
				msleep(100);
				continue;
			}
		}
		return 0;
	}
	return -ETIMEDOUT;
#undef MAX_TRIES
}