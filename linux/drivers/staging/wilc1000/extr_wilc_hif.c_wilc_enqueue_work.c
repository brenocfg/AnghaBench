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
struct host_if_msg {int /*<<< orphan*/  work; TYPE_1__* vif; int /*<<< orphan*/  fn; } ;
struct TYPE_4__ {int /*<<< orphan*/  hif_workqueue; } ;
struct TYPE_3__ {TYPE_2__* wilc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wilc_enqueue_work(struct host_if_msg *msg)
{
	INIT_WORK(&msg->work, msg->fn);

	if (!msg->vif || !msg->vif->wilc || !msg->vif->wilc->hif_workqueue)
		return -EINVAL;

	if (!queue_work(msg->vif->wilc->hif_workqueue, &msg->work))
		return -EINVAL;

	return 0;
}