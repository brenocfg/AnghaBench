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
struct intel_vgpu_type {int /*<<< orphan*/  resolution; int /*<<< orphan*/  weight; int /*<<< orphan*/  fence; void* high_gm_size; void* low_gm_size; } ;
struct intel_vgpu_creation_params {int primary; void* high_gm_sz; void* low_gm_sz; int /*<<< orphan*/  resolution; int /*<<< orphan*/  weight; int /*<<< orphan*/  fence_sz; scalar_t__ handle; } ;
struct intel_vgpu {int dummy; } ;
struct intel_gvt {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 void* BYTES_TO_MB (void*) ; 
 int /*<<< orphan*/  IS_ERR (struct intel_vgpu*) ; 
 struct intel_vgpu* __intel_gvt_create_vgpu (struct intel_gvt*,struct intel_vgpu_creation_params*) ; 
 int /*<<< orphan*/  intel_gvt_update_vgpu_types (struct intel_gvt*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct intel_vgpu *intel_gvt_create_vgpu(struct intel_gvt *gvt,
				struct intel_vgpu_type *type)
{
	struct intel_vgpu_creation_params param;
	struct intel_vgpu *vgpu;

	param.handle = 0;
	param.primary = 1;
	param.low_gm_sz = type->low_gm_size;
	param.high_gm_sz = type->high_gm_size;
	param.fence_sz = type->fence;
	param.weight = type->weight;
	param.resolution = type->resolution;

	/* XXX current param based on MB */
	param.low_gm_sz = BYTES_TO_MB(param.low_gm_sz);
	param.high_gm_sz = BYTES_TO_MB(param.high_gm_sz);

	mutex_lock(&gvt->lock);
	vgpu = __intel_gvt_create_vgpu(gvt, &param);
	if (!IS_ERR(vgpu))
		/* calculate left instance change for types */
		intel_gvt_update_vgpu_types(gvt);
	mutex_unlock(&gvt->lock);

	return vgpu;
}