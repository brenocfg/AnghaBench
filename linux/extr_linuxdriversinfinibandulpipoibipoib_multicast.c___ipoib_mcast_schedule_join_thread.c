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
struct ipoib_mcast {int backoff; scalar_t__ delay_until; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  mcast_task; int /*<<< orphan*/  wq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IPOIB_FLAG_OPER_UP ; 
 int IPOIB_MAX_BACKOFF_SECONDS ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ipoib_mcast_schedule_join_thread(struct ipoib_dev_priv *priv,
					       struct ipoib_mcast *mcast,
					       bool delay)
{
	if (!test_bit(IPOIB_FLAG_OPER_UP, &priv->flags))
		return;

	/*
	 * We will be scheduling *something*, so cancel whatever is
	 * currently scheduled first
	 */
	cancel_delayed_work(&priv->mcast_task);
	if (mcast && delay) {
		/*
		 * We had a failure and want to schedule a retry later
		 */
		mcast->backoff *= 2;
		if (mcast->backoff > IPOIB_MAX_BACKOFF_SECONDS)
			mcast->backoff = IPOIB_MAX_BACKOFF_SECONDS;
		mcast->delay_until = jiffies + (mcast->backoff * HZ);
		/*
		 * Mark this mcast for its delay, but restart the
		 * task immediately.  The join task will make sure to
		 * clear out all entries without delays, and then
		 * schedule itself to run again when the earliest
		 * delay expires
		 */
		queue_delayed_work(priv->wq, &priv->mcast_task, 0);
	} else if (delay) {
		/*
		 * Special case of retrying after a failure to
		 * allocate the broadcast multicast group, wait
		 * 1 second and try again
		 */
		queue_delayed_work(priv->wq, &priv->mcast_task, HZ);
	} else
		queue_delayed_work(priv->wq, &priv->mcast_task, 0);
}