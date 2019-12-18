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
typedef  scalar_t__ u32 ;
struct sg_table {struct scatterlist* sgl; } ;
struct scatterlist {scalar_t__ length; } ;
struct TYPE_4__ {int /*<<< orphan*/  fb; } ;
struct malidp_plane_state {int n_planes; TYPE_1__ base; } ;
struct drm_gem_object {TYPE_3__* dev; } ;
struct drm_gem_cma_object {struct sg_table* sgt; } ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {struct sg_table* (* gem_prime_get_sg_table ) (struct drm_gem_object*) ;} ;

/* Variables and functions */
 struct drm_gem_object* drm_gem_fb_get_obj (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 struct sg_table* stub1 (struct drm_gem_object*) ; 
 struct drm_gem_cma_object* to_drm_gem_cma_obj (struct drm_gem_object*) ; 

__attribute__((used)) static bool malidp_check_pages_threshold(struct malidp_plane_state *ms,
					 u32 pgsize)
{
	int i;

	for (i = 0; i < ms->n_planes; i++) {
		struct drm_gem_object *obj;
		struct drm_gem_cma_object *cma_obj;
		struct sg_table *sgt;
		struct scatterlist *sgl;

		obj = drm_gem_fb_get_obj(ms->base.fb, i);
		cma_obj = to_drm_gem_cma_obj(obj);

		if (cma_obj->sgt)
			sgt = cma_obj->sgt;
		else
			sgt = obj->dev->driver->gem_prime_get_sg_table(obj);

		if (!sgt)
			return false;

		sgl = sgt->sgl;

		while (sgl) {
			if (sgl->length < pgsize) {
				if (!cma_obj->sgt)
					kfree(sgt);
				return false;
			}

			sgl = sg_next(sgl);
		}
		if (!cma_obj->sgt)
			kfree(sgt);
	}

	return true;
}