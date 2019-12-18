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
struct timer_list {int dummy; } ;
struct rsi_common {int /*<<< orphan*/  mutex; int /*<<< orphan*/  roc_timer; TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO_ZONE ; 
 struct rsi_common* common ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct rsi_common* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_remain_on_channel_expired (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roc_timer ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsi_resume_conn_channel (struct rsi_common*) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

void rsi_roc_timeout(struct timer_list *t)
{
	struct rsi_common *common = from_timer(common, t, roc_timer);

	rsi_dbg(INFO_ZONE, "Remain on channel expired\n");

	mutex_lock(&common->mutex);
	ieee80211_remain_on_channel_expired(common->priv->hw);

	if (timer_pending(&common->roc_timer))
		del_timer(&common->roc_timer);

	rsi_resume_conn_channel(common);
	mutex_unlock(&common->mutex);
}