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
struct intel_vgpu_creation_params {int dummy; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int alloc_resource (struct intel_vgpu*,struct intel_vgpu_creation_params*) ; 
 int alloc_vgpu_fence (struct intel_vgpu*) ; 
 int alloc_vgpu_gm (struct intel_vgpu*) ; 
 int /*<<< orphan*/  free_resource (struct intel_vgpu*) ; 
 int /*<<< orphan*/  free_vgpu_gm (struct intel_vgpu*) ; 

int intel_vgpu_alloc_resource(struct intel_vgpu *vgpu,
		struct intel_vgpu_creation_params *param)
{
	int ret;

	ret = alloc_resource(vgpu, param);
	if (ret)
		return ret;

	ret = alloc_vgpu_gm(vgpu);
	if (ret)
		goto out_free_resource;

	ret = alloc_vgpu_fence(vgpu);
	if (ret)
		goto out_free_vgpu_gm;

	return 0;

out_free_vgpu_gm:
	free_vgpu_gm(vgpu);
out_free_resource:
	free_resource(vgpu);
	return ret;
}