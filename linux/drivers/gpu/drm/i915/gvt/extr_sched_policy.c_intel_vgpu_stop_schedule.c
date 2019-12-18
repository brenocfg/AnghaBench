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
struct vgpu_sched_data {int /*<<< orphan*/  active; } ;
struct intel_vgpu {TYPE_2__* gvt; int /*<<< orphan*/  id; struct vgpu_sched_data* sched_data; } ;
struct intel_gvt_workload_scheduler {int need_reschedule; int /*<<< orphan*/  mmio_context_lock; struct intel_vgpu** engine_owner; struct intel_vgpu* current_vgpu; struct intel_vgpu* next_vgpu; TYPE_1__* sched_ops; } ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; } ;
struct TYPE_4__ {int /*<<< orphan*/  sched_lock; struct drm_i915_private* dev_priv; struct intel_gvt_workload_scheduler scheduler; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* stop_schedule ) (struct intel_vgpu*) ;} ;

/* Variables and functions */
 int I915_NUM_ENGINES ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_gvt_switch_mmio (struct intel_vgpu*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put_unchecked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_vgpu*) ; 

void intel_vgpu_stop_schedule(struct intel_vgpu *vgpu)
{
	struct intel_gvt_workload_scheduler *scheduler =
		&vgpu->gvt->scheduler;
	int ring_id;
	struct vgpu_sched_data *vgpu_data = vgpu->sched_data;
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;

	if (!vgpu_data->active)
		return;

	gvt_dbg_core("vgpu%d: stop schedule\n", vgpu->id);

	mutex_lock(&vgpu->gvt->sched_lock);
	scheduler->sched_ops->stop_schedule(vgpu);

	if (scheduler->next_vgpu == vgpu)
		scheduler->next_vgpu = NULL;

	if (scheduler->current_vgpu == vgpu) {
		/* stop workload dispatching */
		scheduler->need_reschedule = true;
		scheduler->current_vgpu = NULL;
	}

	intel_runtime_pm_get(&dev_priv->runtime_pm);
	spin_lock_bh(&scheduler->mmio_context_lock);
	for (ring_id = 0; ring_id < I915_NUM_ENGINES; ring_id++) {
		if (scheduler->engine_owner[ring_id] == vgpu) {
			intel_gvt_switch_mmio(vgpu, NULL, ring_id);
			scheduler->engine_owner[ring_id] = NULL;
		}
	}
	spin_unlock_bh(&scheduler->mmio_context_lock);
	intel_runtime_pm_put_unchecked(&dev_priv->runtime_pm);
	mutex_unlock(&vgpu->gvt->sched_lock);
}