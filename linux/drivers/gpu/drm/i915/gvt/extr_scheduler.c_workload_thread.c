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
struct workload_thread_param {int ring_id; struct intel_gvt* gvt; } ;
struct intel_vgpu_workload {struct intel_vgpu_workload* status; int /*<<< orphan*/  req; struct intel_vgpu_workload* ring_id; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int /*<<< orphan*/  id; } ;
struct intel_runtime_pm {int dummy; } ;
struct intel_gvt_workload_scheduler {int /*<<< orphan*/ * waitq; } ;
struct intel_gvt {TYPE_1__* dev_priv; struct intel_gvt_workload_scheduler scheduler; } ;
struct TYPE_2__ {int /*<<< orphan*/  uncore; struct intel_runtime_pm runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GVT_FAILSAFE_GUEST_ERR ; 
 int INTEL_GEN (TYPE_1__*) ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_current_workload (struct intel_gvt*,int) ; 
 int dispatch_workload (struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  enter_failsafe_mode (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int) ; 
 int /*<<< orphan*/  gvt_dbg_sched (char*,struct intel_vgpu_workload*,struct intel_vgpu_workload*,...) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 int /*<<< orphan*/  i915_request_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put_unchecked (struct intel_runtime_pm*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct workload_thread_param*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 struct intel_vgpu_workload* pick_next_workload (struct intel_gvt*,int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_vreg_in_ctx (struct intel_vgpu_workload*) ; 
 scalar_t__ vgpu_is_vm_unhealthy (int) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_woken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int workload_thread(void *priv)
{
	struct workload_thread_param *p = (struct workload_thread_param *)priv;
	struct intel_gvt *gvt = p->gvt;
	int ring_id = p->ring_id;
	struct intel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	struct intel_vgpu_workload *workload = NULL;
	struct intel_vgpu *vgpu = NULL;
	int ret;
	bool need_force_wake = (INTEL_GEN(gvt->dev_priv) >= 9);
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	struct intel_runtime_pm *rpm = &gvt->dev_priv->runtime_pm;

	kfree(p);

	gvt_dbg_core("workload thread for ring %d started\n", ring_id);

	while (!kthread_should_stop()) {
		add_wait_queue(&scheduler->waitq[ring_id], &wait);
		do {
			workload = pick_next_workload(gvt, ring_id);
			if (workload)
				break;
			wait_woken(&wait, TASK_INTERRUPTIBLE,
				   MAX_SCHEDULE_TIMEOUT);
		} while (!kthread_should_stop());
		remove_wait_queue(&scheduler->waitq[ring_id], &wait);

		if (!workload)
			break;

		gvt_dbg_sched("ring id %d next workload %p vgpu %d\n",
				workload->ring_id, workload,
				workload->vgpu->id);

		intel_runtime_pm_get(rpm);

		gvt_dbg_sched("ring id %d will dispatch workload %p\n",
				workload->ring_id, workload);

		if (need_force_wake)
			intel_uncore_forcewake_get(&gvt->dev_priv->uncore,
					FORCEWAKE_ALL);
		/*
		 * Update the vReg of the vGPU which submitted this
		 * workload. The vGPU may use these registers for checking
		 * the context state. The value comes from GPU commands
		 * in this workload.
		 */
		update_vreg_in_ctx(workload);

		ret = dispatch_workload(workload);

		if (ret) {
			vgpu = workload->vgpu;
			gvt_vgpu_err("fail to dispatch workload, skip\n");
			goto complete;
		}

		gvt_dbg_sched("ring id %d wait workload %p\n",
				workload->ring_id, workload);
		i915_request_wait(workload->req, 0, MAX_SCHEDULE_TIMEOUT);

complete:
		gvt_dbg_sched("will complete workload %p, status: %d\n",
				workload, workload->status);

		complete_current_workload(gvt, ring_id);

		if (need_force_wake)
			intel_uncore_forcewake_put(&gvt->dev_priv->uncore,
					FORCEWAKE_ALL);

		intel_runtime_pm_put_unchecked(rpm);
		if (ret && (vgpu_is_vm_unhealthy(ret)))
			enter_failsafe_mode(vgpu, GVT_FAILSAFE_GUEST_ERR);
	}
	return 0;
}