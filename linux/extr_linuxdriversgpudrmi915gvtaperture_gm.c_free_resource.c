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
struct intel_vgpu {struct intel_gvt* gvt; } ;
struct TYPE_4__ {int /*<<< orphan*/  vgpu_allocated_fence_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  vgpu_allocated_high_gm_size; int /*<<< orphan*/  vgpu_allocated_low_gm_size; } ;
struct intel_gvt {TYPE_2__ fence; TYPE_1__ gm; } ;

/* Variables and functions */
 scalar_t__ vgpu_aperture_sz (struct intel_vgpu*) ; 
 scalar_t__ vgpu_fence_sz (struct intel_vgpu*) ; 
 scalar_t__ vgpu_hidden_sz (struct intel_vgpu*) ; 

__attribute__((used)) static void free_resource(struct intel_vgpu *vgpu)
{
	struct intel_gvt *gvt = vgpu->gvt;

	gvt->gm.vgpu_allocated_low_gm_size -= vgpu_aperture_sz(vgpu);
	gvt->gm.vgpu_allocated_high_gm_size -= vgpu_hidden_sz(vgpu);
	gvt->fence.vgpu_allocated_fence_num -= vgpu_fence_sz(vgpu);
}