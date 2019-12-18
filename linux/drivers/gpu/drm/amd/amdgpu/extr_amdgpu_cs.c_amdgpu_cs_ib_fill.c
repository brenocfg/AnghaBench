#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_sched_entity {TYPE_2__* rq; } ;
struct drm_amdgpu_cs_chunk_ib {scalar_t__ ip_type; int flags; int ib_bytes; int /*<<< orphan*/  va_start; int /*<<< orphan*/  ring; int /*<<< orphan*/  ip_instance; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_ring {TYPE_4__* funcs; } ;
struct amdgpu_ib {int length_dw; int flags; int /*<<< orphan*/  gpu_addr; } ;
struct amdgpu_fpriv {struct amdgpu_vm vm; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_cs_parser {int nchunks; struct drm_sched_entity* entity; int /*<<< orphan*/  ctx; TYPE_3__* job; struct amdgpu_cs_chunk* chunks; TYPE_1__* filp; } ;
struct amdgpu_cs_chunk {scalar_t__ chunk_id; scalar_t__ kdata; } ;
struct TYPE_8__ {scalar_t__ no_user_fence; scalar_t__ parse_cs; } ;
struct TYPE_7__ {int num_ibs; scalar_t__ uf_addr; int /*<<< orphan*/  preamble_status; struct amdgpu_ib* ibs; } ;
struct TYPE_6__ {int /*<<< orphan*/  sched; } ;
struct TYPE_5__ {struct amdgpu_fpriv* driver_priv; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_CHUNK_ID_IB ; 
 scalar_t__ AMDGPU_HW_IP_GFX ; 
 int AMDGPU_IB_FLAG_CE ; 
 int AMDGPU_IB_FLAG_PREAMBLE ; 
 int AMDGPU_IB_FLAG_PREEMPT ; 
 int /*<<< orphan*/  AMDGPU_PREAMBLE_IB_PRESENT ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int amdgpu_ctx_get_entity (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_sched_entity**) ; 
 int amdgpu_ctx_wait_prev_fence (int /*<<< orphan*/ ,struct drm_sched_entity*) ; 
 int amdgpu_ib_get (struct amdgpu_device*,struct amdgpu_vm*,int,struct amdgpu_ib*) ; 
 scalar_t__ amdgpu_mcbp ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 struct amdgpu_ring* to_amdgpu_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_cs_ib_fill(struct amdgpu_device *adev,
			     struct amdgpu_cs_parser *parser)
{
	struct amdgpu_fpriv *fpriv = parser->filp->driver_priv;
	struct amdgpu_vm *vm = &fpriv->vm;
	int r, ce_preempt = 0, de_preempt = 0;
	struct amdgpu_ring *ring;
	int i, j;

	for (i = 0, j = 0; i < parser->nchunks && j < parser->job->num_ibs; i++) {
		struct amdgpu_cs_chunk *chunk;
		struct amdgpu_ib *ib;
		struct drm_amdgpu_cs_chunk_ib *chunk_ib;
		struct drm_sched_entity *entity;

		chunk = &parser->chunks[i];
		ib = &parser->job->ibs[j];
		chunk_ib = (struct drm_amdgpu_cs_chunk_ib *)chunk->kdata;

		if (chunk->chunk_id != AMDGPU_CHUNK_ID_IB)
			continue;

		if (chunk_ib->ip_type == AMDGPU_HW_IP_GFX &&
		    (amdgpu_mcbp || amdgpu_sriov_vf(adev))) {
			if (chunk_ib->flags & AMDGPU_IB_FLAG_PREEMPT) {
				if (chunk_ib->flags & AMDGPU_IB_FLAG_CE)
					ce_preempt++;
				else
					de_preempt++;
			}

			/* each GFX command submit allows 0 or 1 IB preemptible for CE & DE */
			if (ce_preempt > 1 || de_preempt > 1)
				return -EINVAL;
		}

		r = amdgpu_ctx_get_entity(parser->ctx, chunk_ib->ip_type,
					  chunk_ib->ip_instance, chunk_ib->ring,
					  &entity);
		if (r)
			return r;

		if (chunk_ib->flags & AMDGPU_IB_FLAG_PREAMBLE)
			parser->job->preamble_status |=
				AMDGPU_PREAMBLE_IB_PRESENT;

		if (parser->entity && parser->entity != entity)
			return -EINVAL;

		parser->entity = entity;

		ring = to_amdgpu_ring(entity->rq->sched);
		r =  amdgpu_ib_get(adev, vm, ring->funcs->parse_cs ?
				   chunk_ib->ib_bytes : 0, ib);
		if (r) {
			DRM_ERROR("Failed to get ib !\n");
			return r;
		}

		ib->gpu_addr = chunk_ib->va_start;
		ib->length_dw = chunk_ib->ib_bytes / 4;
		ib->flags = chunk_ib->flags;

		j++;
	}

	/* MM engine doesn't support user fences */
	ring = to_amdgpu_ring(parser->entity->rq->sched);
	if (parser->job->uf_addr && ring->funcs->no_user_fence)
		return -EINVAL;

	return amdgpu_ctx_wait_prev_fence(parser->ctx, parser->entity);
}