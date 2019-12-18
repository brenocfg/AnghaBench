#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mp; } ;
struct subchannel {int /*<<< orphan*/  vpm; TYPE_3__ config; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_2__* private; TYPE_4__ dev; } ;
struct ccw_dev_id {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_5__ {int mpath; int pgroup; } ;
struct TYPE_6__ {TYPE_1__ flags; struct ccw_dev_id dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_verify_done (struct ccw_device*,int) ; 
 int cio_commit_config (struct subchannel*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void verify_done(struct ccw_device *cdev, int rc)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct ccw_dev_id *id = &cdev->private->dev_id;
	int mpath = cdev->private->flags.mpath;
	int pgroup = cdev->private->flags.pgroup;

	if (rc)
		goto out;
	/* Ensure consistent multipathing state at device and channel. */
	if (sch->config.mp != mpath) {
		sch->config.mp = mpath;
		rc = cio_commit_config(sch);
	}
out:
	CIO_MSG_EVENT(2, "vrfy: device 0.%x.%04x: rc=%d pgroup=%d mpath=%d "
			 "vpm=%02x\n", id->ssid, id->devno, rc, pgroup, mpath,
			 sch->vpm);
	ccw_device_verify_done(cdev, rc);
}