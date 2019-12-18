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
struct nvmet_ctrl {int /*<<< orphan*/  ka_work; int /*<<< orphan*/  cntlid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvmet_stop_keep_alive_timer(struct nvmet_ctrl *ctrl)
{
	pr_debug("ctrl %d stop keep-alive\n", ctrl->cntlid);

	cancel_delayed_work_sync(&ctrl->ka_work);
}