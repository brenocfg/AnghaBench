#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct subchannel {int opm; scalar_t__ vpm; } ;
struct ccw_request {int lpm; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_3__* private; TYPE_1__ dev; } ;
struct TYPE_5__ {scalar_t__ pgid_unknown; scalar_t__ mpath; } ;
struct TYPE_6__ {TYPE_2__ flags; int /*<<< orphan*/  pgid_todo_mask; struct ccw_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  SPID_FUNC_ESTABLISH ; 
 int /*<<< orphan*/  SPID_FUNC_MULTI_PATH ; 
 int /*<<< orphan*/  SPID_FUNC_RESIGN ; 
 int /*<<< orphan*/  ccw_request_start (struct ccw_device*) ; 
 int lpm_adjust (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgid_wipeout_start (struct ccw_device*) ; 
 int /*<<< orphan*/  spid_build_cp (struct ccw_device*,int /*<<< orphan*/ ) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_done (struct ccw_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spid_do(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw_request *req = &cdev->private->req;
	u8 fn;

	/* Use next available path that is not already in correct state. */
	req->lpm = lpm_adjust(req->lpm, cdev->private->pgid_todo_mask);
	if (!req->lpm)
		goto out_nopath;
	/* Channel program setup. */
	if (req->lpm & sch->opm)
		fn = SPID_FUNC_ESTABLISH;
	else
		fn = SPID_FUNC_RESIGN;
	if (cdev->private->flags.mpath)
		fn |= SPID_FUNC_MULTI_PATH;
	spid_build_cp(cdev, fn);
	ccw_request_start(cdev);
	return;

out_nopath:
	if (cdev->private->flags.pgid_unknown) {
		/* At least one SPID could be partially done. */
		pgid_wipeout_start(cdev);
		return;
	}
	verify_done(cdev, sch->vpm ? 0 : -EACCES);
}