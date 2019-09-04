#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_sched_rq {int dummy; } ;
struct drm_sched_entity {int dummy; } ;
struct TYPE_5__ {struct drm_sched_rq* sched_rq; } ;
struct amdgpu_ring {TYPE_3__* funcs; TYPE_2__ sched; } ;
struct amdgpu_device {int num_rings; struct amdgpu_ring** rings; } ;
struct amdgpu_ctx {int override_priority; int init_priority; TYPE_1__* rings; struct amdgpu_device* adev; } ;
typedef  enum drm_sched_priority { ____Placeholder_drm_sched_priority } drm_sched_priority ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_4__ {struct drm_sched_entity entity; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_RING_TYPE_KIQ ; 
 scalar_t__ DRM_SCHED_PRIORITY_UNSET ; 
 int /*<<< orphan*/  drm_sched_entity_set_rq (struct drm_sched_entity*,struct drm_sched_rq*) ; 

void amdgpu_ctx_priority_override(struct amdgpu_ctx *ctx,
				  enum drm_sched_priority priority)
{
	int i;
	struct amdgpu_device *adev = ctx->adev;
	struct drm_sched_rq *rq;
	struct drm_sched_entity *entity;
	struct amdgpu_ring *ring;
	enum drm_sched_priority ctx_prio;

	ctx->override_priority = priority;

	ctx_prio = (ctx->override_priority == DRM_SCHED_PRIORITY_UNSET) ?
			ctx->init_priority : ctx->override_priority;

	for (i = 0; i < adev->num_rings; i++) {
		ring = adev->rings[i];
		entity = &ctx->rings[i].entity;
		rq = &ring->sched.sched_rq[ctx_prio];

		if (ring->funcs->type == AMDGPU_RING_TYPE_KIQ)
			continue;

		drm_sched_entity_set_rq(entity, rq);
	}
}