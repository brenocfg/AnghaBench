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
struct hl_device_reset_work {int /*<<< orphan*/  reset_work; struct hl_device* hdev; } ;
struct TYPE_5__ {int completion_queues_count; } ;
struct hl_device {int disabled; int hard_reset_pending; int device_cpu_disabled; int /*<<< orphan*/  in_reset; int /*<<< orphan*/  soft_reset_cnt; int /*<<< orphan*/  dev; int /*<<< orphan*/  hard_reset_cnt; TYPE_4__* asic_funcs; int /*<<< orphan*/  max_power; int /*<<< orphan*/ * kernel_ctx; TYPE_3__* compute_ctx; int /*<<< orphan*/  fpriv_list_lock; scalar_t__ cs_active_cnt; TYPE_2__* idle_busy_ts_arr; scalar_t__ idle_busy_ts_idx; int /*<<< orphan*/ * completion_queue; TYPE_1__ asic_prop; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  send_cpu_message_lock; int /*<<< orphan*/  init_done; } ;
struct TYPE_8__ {int (* hw_init ) (struct hl_device*) ;int (* test_queues ) (struct hl_device*) ;int (* soft_reset_late_init ) (struct hl_device*) ;int /*<<< orphan*/  (* hw_fini ) (struct hl_device*,int) ;int /*<<< orphan*/  (* halt_engines ) (struct hl_device*,int) ;int /*<<< orphan*/  (* hw_queues_unlock ) (struct hl_device*) ;int /*<<< orphan*/  (* hw_queues_lock ) (struct hl_device*) ;} ;
struct TYPE_7__ {scalar_t__ thread_ctx_switch_wait_token; int /*<<< orphan*/  thread_ctx_switch_token; } ;
struct TYPE_6__ {void* idle_to_busy_ts; void* busy_to_idle_ts; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_hard_reset_pending ; 
 int /*<<< orphan*/  device_kill_open_processes (struct hl_device*) ; 
 int /*<<< orphan*/  device_late_fini (struct hl_device*) ; 
 int device_late_init (struct hl_device*) ; 
 int /*<<< orphan*/  hl_cq_reset (struct hl_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hl_cs_rollback_all (struct hl_device*) ; 
 int hl_ctx_init (struct hl_device*,int /*<<< orphan*/ *,int) ; 
 int hl_ctx_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hl_eq_reset (struct hl_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hl_hw_queue_reset (struct hl_device*,int) ; 
 int /*<<< orphan*/  hl_mmu_fini (struct hl_device*) ; 
 int hl_mmu_init (struct hl_device*) ; 
 int /*<<< orphan*/  hl_set_max_power (struct hl_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_vm_fini (struct hl_device*) ; 
 int hl_vm_init (struct hl_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*) ; 
 int /*<<< orphan*/  stub2 (struct hl_device*) ; 
 int /*<<< orphan*/  stub3 (struct hl_device*,int) ; 
 int /*<<< orphan*/  stub4 (struct hl_device*,int) ; 
 int stub5 (struct hl_device*) ; 
 int stub6 (struct hl_device*) ; 
 int stub7 (struct hl_device*) ; 

int hl_device_reset(struct hl_device *hdev, bool hard_reset,
			bool from_hard_reset_thread)
{
	int i, rc;

	if (!hdev->init_done) {
		dev_err(hdev->dev,
			"Can't reset before initialization is done\n");
		return 0;
	}

	/*
	 * Prevent concurrency in this function - only one reset should be
	 * done at any given time. Only need to perform this if we didn't
	 * get from the dedicated hard reset thread
	 */
	if (!from_hard_reset_thread) {
		/* Block future CS/VM/JOB completion operations */
		rc = atomic_cmpxchg(&hdev->in_reset, 0, 1);
		if (rc)
			return 0;

		/* This also blocks future CS/VM/JOB completion operations */
		hdev->disabled = true;

		/* Flush anyone that is inside the critical section of enqueue
		 * jobs to the H/W
		 */
		hdev->asic_funcs->hw_queues_lock(hdev);
		hdev->asic_funcs->hw_queues_unlock(hdev);

		/* Flush anyone that is inside device open */
		mutex_lock(&hdev->fpriv_list_lock);
		mutex_unlock(&hdev->fpriv_list_lock);

		dev_err(hdev->dev, "Going to RESET device!\n");
	}

again:
	if ((hard_reset) && (!from_hard_reset_thread)) {
		struct hl_device_reset_work *device_reset_work;

		hdev->hard_reset_pending = true;

		device_reset_work = kzalloc(sizeof(*device_reset_work),
						GFP_ATOMIC);
		if (!device_reset_work) {
			rc = -ENOMEM;
			goto out_err;
		}

		/*
		 * Because the reset function can't run from interrupt or
		 * from heartbeat work, we need to call the reset function
		 * from a dedicated work
		 */
		INIT_WORK(&device_reset_work->reset_work,
				device_hard_reset_pending);
		device_reset_work->hdev = hdev;
		schedule_work(&device_reset_work->reset_work);

		return 0;
	}

	if (hard_reset) {
		device_late_fini(hdev);

		/*
		 * Now that the heartbeat thread is closed, flush processes
		 * which are sending messages to CPU
		 */
		mutex_lock(&hdev->send_cpu_message_lock);
		mutex_unlock(&hdev->send_cpu_message_lock);
	}

	/*
	 * Halt the engines and disable interrupts so we won't get any more
	 * completions from H/W and we won't have any accesses from the
	 * H/W to the host machine
	 */
	hdev->asic_funcs->halt_engines(hdev, hard_reset);

	/* Go over all the queues, release all CS and their jobs */
	hl_cs_rollback_all(hdev);

	/* Kill processes here after CS rollback. This is because the process
	 * can't really exit until all its CSs are done, which is what we
	 * do in cs rollback
	 */
	if (from_hard_reset_thread)
		device_kill_open_processes(hdev);

	/* Release kernel context */
	if ((hard_reset) && (hl_ctx_put(hdev->kernel_ctx) == 1))
		hdev->kernel_ctx = NULL;

	/* Reset the H/W. It will be in idle state after this returns */
	hdev->asic_funcs->hw_fini(hdev, hard_reset);

	if (hard_reset) {
		hl_vm_fini(hdev);
		hl_mmu_fini(hdev);
		hl_eq_reset(hdev, &hdev->event_queue);
	}

	/* Re-initialize PI,CI to 0 in all queues (hw queue, cq) */
	hl_hw_queue_reset(hdev, hard_reset);
	for (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++)
		hl_cq_reset(hdev, &hdev->completion_queue[i]);

	hdev->idle_busy_ts_idx = 0;
	hdev->idle_busy_ts_arr[0].busy_to_idle_ts = ktime_set(0, 0);
	hdev->idle_busy_ts_arr[0].idle_to_busy_ts = ktime_set(0, 0);

	if (hdev->cs_active_cnt)
		dev_crit(hdev->dev, "CS active cnt %d is not 0 during reset\n",
			hdev->cs_active_cnt);

	mutex_lock(&hdev->fpriv_list_lock);

	/* Make sure the context switch phase will run again */
	if (hdev->compute_ctx) {
		atomic_set(&hdev->compute_ctx->thread_ctx_switch_token, 1);
		hdev->compute_ctx->thread_ctx_switch_wait_token = 0;
	}

	mutex_unlock(&hdev->fpriv_list_lock);

	/* Finished tear-down, starting to re-initialize */

	if (hard_reset) {
		hdev->device_cpu_disabled = false;
		hdev->hard_reset_pending = false;

		if (hdev->kernel_ctx) {
			dev_crit(hdev->dev,
				"kernel ctx was alive during hard reset, something is terribly wrong\n");
			rc = -EBUSY;
			goto out_err;
		}

		rc = hl_mmu_init(hdev);
		if (rc) {
			dev_err(hdev->dev,
				"Failed to initialize MMU S/W after hard reset\n");
			goto out_err;
		}

		/* Allocate the kernel context */
		hdev->kernel_ctx = kzalloc(sizeof(*hdev->kernel_ctx),
						GFP_KERNEL);
		if (!hdev->kernel_ctx) {
			rc = -ENOMEM;
			goto out_err;
		}

		hdev->compute_ctx = NULL;

		rc = hl_ctx_init(hdev, hdev->kernel_ctx, true);
		if (rc) {
			dev_err(hdev->dev,
				"failed to init kernel ctx in hard reset\n");
			kfree(hdev->kernel_ctx);
			hdev->kernel_ctx = NULL;
			goto out_err;
		}
	}

	rc = hdev->asic_funcs->hw_init(hdev);
	if (rc) {
		dev_err(hdev->dev,
			"failed to initialize the H/W after reset\n");
		goto out_err;
	}

	hdev->disabled = false;

	/* Check that the communication with the device is working */
	rc = hdev->asic_funcs->test_queues(hdev);
	if (rc) {
		dev_err(hdev->dev,
			"Failed to detect if device is alive after reset\n");
		goto out_err;
	}

	if (hard_reset) {
		rc = device_late_init(hdev);
		if (rc) {
			dev_err(hdev->dev,
				"Failed late init after hard reset\n");
			goto out_err;
		}

		rc = hl_vm_init(hdev);
		if (rc) {
			dev_err(hdev->dev,
				"Failed to init memory module after hard reset\n");
			goto out_err;
		}

		hl_set_max_power(hdev, hdev->max_power);
	} else {
		rc = hdev->asic_funcs->soft_reset_late_init(hdev);
		if (rc) {
			dev_err(hdev->dev,
				"Failed late init after soft reset\n");
			goto out_err;
		}
	}

	atomic_set(&hdev->in_reset, 0);

	if (hard_reset)
		hdev->hard_reset_cnt++;
	else
		hdev->soft_reset_cnt++;

	dev_warn(hdev->dev, "Successfully finished resetting the device\n");

	return 0;

out_err:
	hdev->disabled = true;

	if (hard_reset) {
		dev_err(hdev->dev,
			"Failed to reset! Device is NOT usable\n");
		hdev->hard_reset_cnt++;
	} else {
		dev_err(hdev->dev,
			"Failed to do soft-reset, trying hard reset\n");
		hdev->soft_reset_cnt++;
		hard_reset = true;
		goto again;
	}

	atomic_set(&hdev->in_reset, 0);

	return rc;
}