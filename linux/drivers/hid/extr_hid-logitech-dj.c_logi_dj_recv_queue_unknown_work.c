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
typedef  int /*<<< orphan*/  workitem ;
struct dj_workitem {int /*<<< orphan*/  type; } ;
struct dj_receiver_dev {int /*<<< orphan*/  work; int /*<<< orphan*/  notif_fifo; scalar_t__ last_query; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  WORKITEM_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,struct dj_workitem*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void logi_dj_recv_queue_unknown_work(struct dj_receiver_dev *djrcv_dev)
{
	struct dj_workitem workitem = { .type = WORKITEM_TYPE_UNKNOWN };

	/* Rate limit queries done because of unhandeled reports to 2/sec */
	if (time_before(jiffies, djrcv_dev->last_query + HZ / 2))
		return;

	kfifo_in(&djrcv_dev->notif_fifo, &workitem, sizeof(workitem));
	schedule_work(&djrcv_dev->work);
}