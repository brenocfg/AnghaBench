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
typedef  int uint32_t ;
struct drm_gem_object {int dummy; } ;
struct drm_amdgpu_cs_chunk_fence {int offset; int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int num_shared; TYPE_3__* bo; } ;
struct TYPE_5__ {TYPE_1__ tv; scalar_t__ priority; } ;
struct amdgpu_cs_parser {TYPE_2__ uf_entry; int /*<<< orphan*/  filp; } ;
struct TYPE_6__ {int /*<<< orphan*/  ttm; } ;
struct amdgpu_bo {TYPE_3__ tbo; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SIZE ; 
 struct amdgpu_bo* amdgpu_bo_ref (int /*<<< orphan*/ ) ; 
 unsigned long amdgpu_bo_size (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 scalar_t__ amdgpu_ttm_tt_get_usermm (int /*<<< orphan*/ ) ; 
 struct drm_gem_object* drm_gem_object_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  gem_to_amdgpu_bo (struct drm_gem_object*) ; 

__attribute__((used)) static int amdgpu_cs_user_fence_chunk(struct amdgpu_cs_parser *p,
				      struct drm_amdgpu_cs_chunk_fence *data,
				      uint32_t *offset)
{
	struct drm_gem_object *gobj;
	struct amdgpu_bo *bo;
	unsigned long size;
	int r;

	gobj = drm_gem_object_lookup(p->filp, data->handle);
	if (gobj == NULL)
		return -EINVAL;

	bo = amdgpu_bo_ref(gem_to_amdgpu_bo(gobj));
	p->uf_entry.priority = 0;
	p->uf_entry.tv.bo = &bo->tbo;
	/* One for TTM and one for the CS job */
	p->uf_entry.tv.num_shared = 2;

	drm_gem_object_put_unlocked(gobj);

	size = amdgpu_bo_size(bo);
	if (size != PAGE_SIZE || (data->offset + 8) > size) {
		r = -EINVAL;
		goto error_unref;
	}

	if (amdgpu_ttm_tt_get_usermm(bo->tbo.ttm)) {
		r = -EINVAL;
		goto error_unref;
	}

	*offset = data->offset;

	return 0;

error_unref:
	amdgpu_bo_unref(&bo);
	return r;
}