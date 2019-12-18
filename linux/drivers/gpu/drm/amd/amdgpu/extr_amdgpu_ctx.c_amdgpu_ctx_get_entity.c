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
typedef  scalar_t__ u32 ;
struct drm_sched_entity {int dummy; } ;
struct amdgpu_ctx {TYPE_1__** entities; } ;
struct TYPE_2__ {struct drm_sched_entity entity; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_HW_IP_NUM ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__* amdgpu_ctx_num_entities ; 

int amdgpu_ctx_get_entity(struct amdgpu_ctx *ctx, u32 hw_ip, u32 instance,
			  u32 ring, struct drm_sched_entity **entity)
{
	if (hw_ip >= AMDGPU_HW_IP_NUM) {
		DRM_ERROR("unknown HW IP type: %d\n", hw_ip);
		return -EINVAL;
	}

	/* Right now all IPs have only one instance - multiple rings. */
	if (instance != 0) {
		DRM_DEBUG("invalid ip instance: %d\n", instance);
		return -EINVAL;
	}

	if (ring >= amdgpu_ctx_num_entities[hw_ip]) {
		DRM_DEBUG("invalid ring: %d %d\n", hw_ip, ring);
		return -EINVAL;
	}

	*entity = &ctx->entities[hw_ip][ring].entity;
	return 0;
}