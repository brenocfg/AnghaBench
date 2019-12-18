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
 int /*<<< orphan*/  intel_gvt_reset_vgpu_locked (struct intel_vgpu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_gvt_reset_vgpu(struct intel_vgpu *vgpu)
{
	mutex_lock(&vgpu->vgpu_lock);
	intel_gvt_reset_vgpu_locked(vgpu, true, 0);
	mutex_unlock(&vgpu->vgpu_lock);
}