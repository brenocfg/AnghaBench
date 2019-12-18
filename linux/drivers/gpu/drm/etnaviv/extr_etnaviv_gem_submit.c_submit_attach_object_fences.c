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
struct etnaviv_gem_submit {int nr_bos; int /*<<< orphan*/  out_fence; TYPE_2__* bos; } ;
struct drm_gem_object {int /*<<< orphan*/  resv; } ;
struct TYPE_4__ {int flags; TYPE_1__* obj; } ;
struct TYPE_3__ {struct drm_gem_object base; } ;

/* Variables and functions */
 int ETNA_SUBMIT_BO_WRITE ; 
 int /*<<< orphan*/  dma_resv_add_excl_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_resv_add_shared_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_unlock_object (struct etnaviv_gem_submit*,int) ; 

__attribute__((used)) static void submit_attach_object_fences(struct etnaviv_gem_submit *submit)
{
	int i;

	for (i = 0; i < submit->nr_bos; i++) {
		struct drm_gem_object *obj = &submit->bos[i].obj->base;

		if (submit->bos[i].flags & ETNA_SUBMIT_BO_WRITE)
			dma_resv_add_excl_fence(obj->resv,
							  submit->out_fence);
		else
			dma_resv_add_shared_fence(obj->resv,
							    submit->out_fence);

		submit_unlock_object(submit, i);
	}
}