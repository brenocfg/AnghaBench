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
 int /*<<< orphan*/  ALL_ENGINES ; 
 int /*<<< orphan*/  intel_gvt_deactivate_vgpu (struct intel_vgpu*) ; 
 int /*<<< orphan*/  intel_vgpu_clean_workloads (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_vgpu_dmabuf_cleanup (struct intel_vgpu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_gvt_release_vgpu(struct intel_vgpu *vgpu)
{
	intel_gvt_deactivate_vgpu(vgpu);

	mutex_lock(&vgpu->vgpu_lock);
	intel_vgpu_clean_workloads(vgpu, ALL_ENGINES);
	intel_vgpu_dmabuf_cleanup(vgpu);
	mutex_unlock(&vgpu->vgpu_lock);
}