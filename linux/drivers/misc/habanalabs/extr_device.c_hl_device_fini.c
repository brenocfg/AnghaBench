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
struct TYPE_3__ {int completion_queues_count; } ;
struct hl_device {int disabled; int hard_reset_pending; TYPE_2__* asic_funcs; int /*<<< orphan*/ * completion_queue; TYPE_1__ asic_prop; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  dev; scalar_t__ kernel_ctx; int /*<<< orphan*/  fpriv_list_lock; int /*<<< orphan*/  in_reset; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* sw_fini ) (struct hl_device*) ;int /*<<< orphan*/  (* hw_fini ) (struct hl_device*,int) ;int /*<<< orphan*/  (* halt_engines ) (struct hl_device*,int) ;int /*<<< orphan*/  (* hw_queues_unlock ) (struct hl_device*) ;int /*<<< orphan*/  (* hw_queues_lock ) (struct hl_device*) ;} ;

/* Variables and functions */
 int HL_PENDING_RESET_PER_SEC ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_cdev_sysfs_del (struct hl_device*) ; 
 int /*<<< orphan*/  device_early_fini (struct hl_device*) ; 
 int /*<<< orphan*/  device_kill_open_processes (struct hl_device*) ; 
 int /*<<< orphan*/  device_late_fini (struct hl_device*) ; 
 int /*<<< orphan*/  hl_cb_pool_fini (struct hl_device*) ; 
 int /*<<< orphan*/  hl_cq_fini (struct hl_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hl_cs_rollback_all (struct hl_device*) ; 
 int hl_ctx_put (scalar_t__) ; 
 int /*<<< orphan*/  hl_debugfs_remove_device (struct hl_device*) ; 
 int /*<<< orphan*/  hl_eq_fini (struct hl_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hl_hw_queues_destroy (struct hl_device*) ; 
 int /*<<< orphan*/  hl_hwmon_fini (struct hl_device*) ; 
 int /*<<< orphan*/  hl_mmu_fini (struct hl_device*) ; 
 int /*<<< orphan*/  hl_vm_fini (struct hl_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*) ; 
 int /*<<< orphan*/  stub2 (struct hl_device*) ; 
 int /*<<< orphan*/  stub3 (struct hl_device*,int) ; 
 int /*<<< orphan*/  stub4 (struct hl_device*,int) ; 
 int /*<<< orphan*/  stub5 (struct hl_device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void hl_device_fini(struct hl_device *hdev)
{
	int i, rc;
	ktime_t timeout;

	dev_info(hdev->dev, "Removing device\n");

	/*
	 * This function is competing with the reset function, so try to
	 * take the reset atomic and if we are already in middle of reset,
	 * wait until reset function is finished. Reset function is designed
	 * to always finish (could take up to a few seconds in worst case).
	 */

	timeout = ktime_add_us(ktime_get(),
				HL_PENDING_RESET_PER_SEC * 1000 * 1000 * 4);
	rc = atomic_cmpxchg(&hdev->in_reset, 0, 1);
	while (rc) {
		usleep_range(50, 200);
		rc = atomic_cmpxchg(&hdev->in_reset, 0, 1);
		if (ktime_compare(ktime_get(), timeout) > 0) {
			WARN(1, "Failed to remove device because reset function did not finish\n");
			return;
		}
	}

	/* Mark device as disabled */
	hdev->disabled = true;

	/* Flush anyone that is inside the critical section of enqueue
	 * jobs to the H/W
	 */
	hdev->asic_funcs->hw_queues_lock(hdev);
	hdev->asic_funcs->hw_queues_unlock(hdev);

	/* Flush anyone that is inside device open */
	mutex_lock(&hdev->fpriv_list_lock);
	mutex_unlock(&hdev->fpriv_list_lock);

	hdev->hard_reset_pending = true;

	hl_hwmon_fini(hdev);

	device_late_fini(hdev);

	hl_debugfs_remove_device(hdev);

	/*
	 * Halt the engines and disable interrupts so we won't get any more
	 * completions from H/W and we won't have any accesses from the
	 * H/W to the host machine
	 */
	hdev->asic_funcs->halt_engines(hdev, true);

	/* Go over all the queues, release all CS and their jobs */
	hl_cs_rollback_all(hdev);

	/* Kill processes here after CS rollback. This is because the process
	 * can't really exit until all its CSs are done, which is what we
	 * do in cs rollback
	 */
	device_kill_open_processes(hdev);

	hl_cb_pool_fini(hdev);

	/* Release kernel context */
	if ((hdev->kernel_ctx) && (hl_ctx_put(hdev->kernel_ctx) != 1))
		dev_err(hdev->dev, "kernel ctx is still alive\n");

	/* Reset the H/W. It will be in idle state after this returns */
	hdev->asic_funcs->hw_fini(hdev, true);

	hl_vm_fini(hdev);

	hl_mmu_fini(hdev);

	hl_eq_fini(hdev, &hdev->event_queue);

	for (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++)
		hl_cq_fini(hdev, &hdev->completion_queue[i]);
	kfree(hdev->completion_queue);

	hl_hw_queues_destroy(hdev);

	/* Call ASIC S/W finalize function */
	hdev->asic_funcs->sw_fini(hdev);

	device_early_fini(hdev);

	/* Hide devices and sysfs nodes from user */
	device_cdev_sysfs_del(hdev);

	pr_info("removed device successfully\n");
}