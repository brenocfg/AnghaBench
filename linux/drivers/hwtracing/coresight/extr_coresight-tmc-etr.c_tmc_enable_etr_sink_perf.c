#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tmc_drvdata {scalar_t__ mode; int pid; int /*<<< orphan*/  spinlock; scalar_t__ perf_buf; } ;
struct perf_output_handle {int /*<<< orphan*/  head; } ;
struct etr_perf_buffer {int pid; scalar_t__ etr_buf; int /*<<< orphan*/  head; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {int /*<<< orphan*/  refcnt; TYPE_1__ dev; } ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ CS_MODE_PERF ; 
 scalar_t__ CS_MODE_SYSFS ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  PERF_IDX2OFF (int /*<<< orphan*/ ,struct etr_perf_buffer*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ ) ; 
 struct tmc_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct etr_perf_buffer* etm_perf_sink_config (struct perf_output_handle*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tmc_etr_enable_hw (struct tmc_drvdata*,scalar_t__) ; 

__attribute__((used)) static int tmc_enable_etr_sink_perf(struct coresight_device *csdev, void *data)
{
	int rc = 0;
	pid_t pid;
	unsigned long flags;
	struct tmc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	struct perf_output_handle *handle = data;
	struct etr_perf_buffer *etr_perf = etm_perf_sink_config(handle);

	spin_lock_irqsave(&drvdata->spinlock, flags);
	 /* Don't use this sink if it is already claimed by sysFS */
	if (drvdata->mode == CS_MODE_SYSFS) {
		rc = -EBUSY;
		goto unlock_out;
	}

	if (WARN_ON(!etr_perf || !etr_perf->etr_buf)) {
		rc = -EINVAL;
		goto unlock_out;
	}

	/* Get a handle on the pid of the process to monitor */
	pid = etr_perf->pid;

	/* Do not proceed if this device is associated with another session */
	if (drvdata->pid != -1 && drvdata->pid != pid) {
		rc = -EBUSY;
		goto unlock_out;
	}

	etr_perf->head = PERF_IDX2OFF(handle->head, etr_perf);

	/*
	 * No HW configuration is needed if the sink is already in
	 * use for this session.
	 */
	if (drvdata->pid == pid) {
		atomic_inc(csdev->refcnt);
		goto unlock_out;
	}

	rc = tmc_etr_enable_hw(drvdata, etr_perf->etr_buf);
	if (!rc) {
		/* Associate with monitored process. */
		drvdata->pid = pid;
		drvdata->mode = CS_MODE_PERF;
		drvdata->perf_buf = etr_perf->etr_buf;
		atomic_inc(csdev->refcnt);
	}

unlock_out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	return rc;
}