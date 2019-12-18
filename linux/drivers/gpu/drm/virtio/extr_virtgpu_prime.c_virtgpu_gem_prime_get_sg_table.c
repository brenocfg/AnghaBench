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
struct TYPE_4__ {TYPE_1__* ttm; } ;
struct virtio_gpu_object {TYPE_2__ tbo; } ;
struct sg_table {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_pages; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct sg_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct sg_table* drm_prime_pages_to_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct virtio_gpu_object* gem_to_virtio_gpu_obj (struct drm_gem_object*) ; 

struct sg_table *virtgpu_gem_prime_get_sg_table(struct drm_gem_object *obj)
{
	struct virtio_gpu_object *bo = gem_to_virtio_gpu_obj(obj);

	if (!bo->tbo.ttm->pages || !bo->tbo.ttm->num_pages)
		/* should not happen */
		return ERR_PTR(-EINVAL);

	return drm_prime_pages_to_sg(bo->tbo.ttm->pages,
				     bo->tbo.ttm->num_pages);
}