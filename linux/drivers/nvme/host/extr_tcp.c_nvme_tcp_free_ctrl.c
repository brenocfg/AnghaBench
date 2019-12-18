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
struct nvme_tcp_ctrl {struct nvme_tcp_ctrl* queues; int /*<<< orphan*/  list; } ;
struct nvme_ctrl {int /*<<< orphan*/  opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvme_tcp_ctrl*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_tcp_ctrl_mutex ; 
 int /*<<< orphan*/  nvmf_free_options (int /*<<< orphan*/ ) ; 
 struct nvme_tcp_ctrl* to_tcp_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_tcp_free_ctrl(struct nvme_ctrl *nctrl)
{
	struct nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);

	if (list_empty(&ctrl->list))
		goto free_ctrl;

	mutex_lock(&nvme_tcp_ctrl_mutex);
	list_del(&ctrl->list);
	mutex_unlock(&nvme_tcp_ctrl_mutex);

	nvmf_free_options(nctrl->opts);
free_ctrl:
	kfree(ctrl->queues);
	kfree(ctrl);
}