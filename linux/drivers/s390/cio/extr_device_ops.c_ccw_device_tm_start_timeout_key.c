#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tcw {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ena; } ;
struct TYPE_8__ {TYPE_2__ pmcw; } ;
struct subchannel {int /*<<< orphan*/  lpm; TYPE_3__ schib; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_5__* private; TYPE_1__ dev; } ;
struct TYPE_9__ {scalar_t__ fake_irb; } ;
struct TYPE_10__ {scalar_t__ state; unsigned long intparm; TYPE_4__ flags; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_ONLINE ; 
 scalar_t__ DEV_STATE_VERIFY ; 
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ FAKE_TM_IRB ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int) ; 
 int cio_tm_start_key (struct subchannel*,struct tcw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

int ccw_device_tm_start_timeout_key(struct ccw_device *cdev, struct tcw *tcw,
				    unsigned long intparm, u8 lpm, u8 key,
				    int expires)
{
	struct subchannel *sch;
	int rc;

	sch = to_subchannel(cdev->dev.parent);
	if (!sch->schib.pmcw.ena)
		return -EINVAL;
	if (cdev->private->state == DEV_STATE_VERIFY) {
		/* Remember to fake irb when finished. */
		if (!cdev->private->flags.fake_irb) {
			cdev->private->flags.fake_irb = FAKE_TM_IRB;
			cdev->private->intparm = intparm;
			return 0;
		} else
			/* There's already a fake I/O around. */
			return -EBUSY;
	}
	if (cdev->private->state != DEV_STATE_ONLINE)
		return -EIO;
	/* Adjust requested path mask to exclude unusable paths. */
	if (lpm) {
		lpm &= sch->lpm;
		if (lpm == 0)
			return -EACCES;
	}
	rc = cio_tm_start_key(sch, tcw, lpm, key);
	if (rc == 0) {
		cdev->private->intparm = intparm;
		if (expires)
			ccw_device_set_timeout(cdev, expires);
	}
	return rc;
}