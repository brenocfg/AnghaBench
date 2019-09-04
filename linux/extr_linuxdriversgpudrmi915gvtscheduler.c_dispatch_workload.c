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
struct intel_vgpu_workload {int ring_id; int status; int dispatched; struct intel_vgpu_workload* req; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int /*<<< orphan*/  vgpu_lock; TYPE_1__* gvt; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct TYPE_3__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  gvt_dbg_sched (char*,int,struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  i915_request_add (struct intel_vgpu_workload*) ; 
 int intel_gvt_scan_and_shadow_workload (struct intel_vgpu_workload*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int prepare_workload (struct intel_vgpu_workload*) ; 

__attribute__((used)) static int dispatch_workload(struct intel_vgpu_workload *workload)
{
	struct intel_vgpu *vgpu = workload->vgpu;
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;
	int ring_id = workload->ring_id;
	int ret;

	gvt_dbg_sched("ring id %d prepare to dispatch workload %p\n",
		ring_id, workload);

	mutex_lock(&vgpu->vgpu_lock);
	mutex_lock(&dev_priv->drm.struct_mutex);

	ret = intel_gvt_scan_and_shadow_workload(workload);
	if (ret)
		goto out;

	ret = prepare_workload(workload);

out:
	if (ret)
		workload->status = ret;

	if (!IS_ERR_OR_NULL(workload->req)) {
		gvt_dbg_sched("ring id %d submit workload to i915 %p\n",
				ring_id, workload->req);
		i915_request_add(workload->req);
		workload->dispatched = true;
	}

	mutex_unlock(&dev_priv->drm.struct_mutex);
	mutex_unlock(&vgpu->vgpu_lock);
	return ret;
}