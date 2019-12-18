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
typedef  size_t uint32_t ;
struct amdgpu_ring {int /*<<< orphan*/  me; } ;
struct amdgpu_ib {unsigned int length_dw; } ;
struct amdgpu_cs_parser {TYPE_4__* adev; TYPE_3__* job; TYPE_2__* entity; } ;
struct TYPE_8__ {scalar_t__*** reg_offset; } ;
struct TYPE_7__ {struct amdgpu_ib* ibs; } ;
struct TYPE_6__ {TYPE_1__* rq; } ;
struct TYPE_5__ {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 size_t UVD_HWIP ; 
 size_t amdgpu_get_ib_value (struct amdgpu_cs_parser*,size_t,unsigned int) ; 
 int /*<<< orphan*/  amdgpu_set_ib_value (struct amdgpu_cs_parser*,size_t,unsigned int,size_t) ; 
 struct amdgpu_ring* to_amdgpu_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uvd_v7_0_ring_patch_cs_in_place(struct amdgpu_cs_parser *p,
					   uint32_t ib_idx)
{
	struct amdgpu_ring *ring = to_amdgpu_ring(p->entity->rq->sched);
	struct amdgpu_ib *ib = &p->job->ibs[ib_idx];
	unsigned i;

	/* No patching necessary for the first instance */
	if (!ring->me)
		return 0;

	for (i = 0; i < ib->length_dw; i += 2) {
		uint32_t reg = amdgpu_get_ib_value(p, ib_idx, i);

		reg -= p->adev->reg_offset[UVD_HWIP][0][1];
		reg += p->adev->reg_offset[UVD_HWIP][1][1];

		amdgpu_set_ib_value(p, ib_idx, i, reg);
	}
	return 0;
}