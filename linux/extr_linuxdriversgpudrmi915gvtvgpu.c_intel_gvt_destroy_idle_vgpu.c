#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_vgpu {int /*<<< orphan*/  vgpu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_vgpu_clean_sched_policy (struct intel_vgpu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (struct intel_vgpu*) ; 

void intel_gvt_destroy_idle_vgpu(struct intel_vgpu *vgpu)
{
	mutex_lock(&vgpu->vgpu_lock);
	intel_vgpu_clean_sched_policy(vgpu);
	mutex_unlock(&vgpu->vgpu_lock);

	vfree(vgpu);
}