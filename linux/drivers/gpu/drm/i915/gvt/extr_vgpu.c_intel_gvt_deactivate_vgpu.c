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
struct TYPE_2__ {int /*<<< orphan*/  running_workload_num; } ;
struct intel_vgpu {int active; int /*<<< orphan*/  vgpu_lock; TYPE_1__ submission; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gvt_wait_vgpu_idle (struct intel_vgpu*) ; 
 int /*<<< orphan*/  intel_vgpu_stop_schedule (struct intel_vgpu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_gvt_deactivate_vgpu(struct intel_vgpu *vgpu)
{
	mutex_lock(&vgpu->vgpu_lock);

	vgpu->active = false;

	if (atomic_read(&vgpu->submission.running_workload_num)) {
		mutex_unlock(&vgpu->vgpu_lock);
		intel_gvt_wait_vgpu_idle(vgpu);
		mutex_lock(&vgpu->vgpu_lock);
	}

	intel_vgpu_stop_schedule(vgpu);

	mutex_unlock(&vgpu->vgpu_lock);
}