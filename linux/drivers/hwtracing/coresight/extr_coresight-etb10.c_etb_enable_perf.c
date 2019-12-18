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
struct perf_output_handle {TYPE_2__* event; } ;
struct etb_drvdata {scalar_t__ mode; int pid; int /*<<< orphan*/  spinlock; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {int /*<<< orphan*/  refcnt; TYPE_1__ dev; } ;
typedef  int pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 scalar_t__ CS_MODE_PERF ; 
 scalar_t__ CS_MODE_SYSFS ; 
 int EBUSY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ ) ; 
 struct etb_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int etb_enable_hw (struct etb_drvdata*) ; 
 int etb_set_buffer (struct coresight_device*,struct perf_output_handle*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int etb_enable_perf(struct coresight_device *csdev, void *data)
{
	int ret = 0;
	pid_t pid;
	unsigned long flags;
	struct etb_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	struct perf_output_handle *handle = data;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* No need to continue if the component is already in used by sysFS. */
	if (drvdata->mode == CS_MODE_SYSFS) {
		ret = -EBUSY;
		goto out;
	}

	/* Get a handle on the pid of the process to monitor */
	pid = task_pid_nr(handle->event->owner);

	if (drvdata->pid != -1 && drvdata->pid != pid) {
		ret = -EBUSY;
		goto out;
	}

	/*
	 * No HW configuration is needed if the sink is already in
	 * use for this session.
	 */
	if (drvdata->pid == pid) {
		atomic_inc(csdev->refcnt);
		goto out;
	}

	/*
	 * We don't have an internal state to clean up if we fail to setup
	 * the perf buffer. So we can perform the step before we turn the
	 * ETB on and leave without cleaning up.
	 */
	ret = etb_set_buffer(csdev, handle);
	if (ret)
		goto out;

	ret = etb_enable_hw(drvdata);
	if (!ret) {
		/* Associate with monitored process. */
		drvdata->pid = pid;
		drvdata->mode = CS_MODE_PERF;
		atomic_inc(csdev->refcnt);
	}

out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	return ret;
}