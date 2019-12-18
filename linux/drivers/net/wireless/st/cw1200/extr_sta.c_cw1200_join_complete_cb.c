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
struct wsm_join_complete {int /*<<< orphan*/  status; } ;
struct cw1200_common {int /*<<< orphan*/  join_complete_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  join_complete_status; int /*<<< orphan*/  join_timeout; } ;

/* Variables and functions */
 scalar_t__ cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cw1200_join_complete_cb(struct cw1200_common *priv,
			     struct wsm_join_complete *arg)
{
	pr_debug("[STA] cw1200_join_complete_cb called, status=%d.\n",
		 arg->status);

	if (cancel_delayed_work(&priv->join_timeout)) {
		priv->join_complete_status = arg->status;
		queue_work(priv->workqueue, &priv->join_complete_work);
	}
}