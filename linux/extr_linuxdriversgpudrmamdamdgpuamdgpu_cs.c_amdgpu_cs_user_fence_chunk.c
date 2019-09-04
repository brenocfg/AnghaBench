#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct drm_gem_object {int dummy; } ;
struct drm_amdgpu_cs_chunk_fence {int offset; int /*<<< orphan*/  handle; } ;
struct TYPE_7__ {int shared; TYPE_2__* bo; } ;
struct TYPE_9__ {TYPE_4__* robj; int /*<<< orphan*/ * user_pages; TYPE_1__ tv; scalar_t__ priority; } ;
struct amdgpu_cs_parser {TYPE_3__ uf_entry; int /*<<< orphan*/  filp; } ;
struct TYPE_8__ {int /*<<< orphan*/  ttm; } ;
struct TYPE_10__ {TYPE_2__ tbo; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SIZE ; 
 TYPE_4__* amdgpu_bo_ref (int /*<<< orphan*/ ) ; 
 unsigned long amdgpu_bo_size (TYPE_4__*) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (TYPE_4__**) ; 
 scalar_t__ amdgpu_ttm_tt_get_usermm (int /*<<< orphan*/ ) ; 
 struct drm_gem_object* drm_gem_object_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  gem_to_amdgpu_bo (struct drm_gem_object*) ; 

__attribute__((used)) static int amdgpu_cs_user_fence_chunk(struct amdgpu_cs_parser *p,
				      struct drm_amdgpu_cs_chunk_fence *data,
				      uint32_t *offset)
{
	struct drm_gem_object *gobj;
	unsigned long size;
	int r;

	gobj = drm_gem_object_lookup(p->filp, data->handle);
	if (gobj == NULL)
		return -EINVAL;

	p->uf_entry.robj = amdgpu_bo_ref(gem_to_amdgpu_bo(gobj));
	p->uf_entry.priority = 0;
	p->uf_entry.tv.bo = &p->uf_entry.robj->tbo;
	p->uf_entry.tv.shared = true;
	p->uf_entry.user_pages = NULL;

	drm_gem_object_put_unlocked(gobj);

	size = amdgpu_bo_size(p->uf_entry.robj);
	if (size != PAGE_SIZE || (data->offset + 8) > size) {
		r = -EINVAL;
		goto error_unref;
	}

	if (amdgpu_ttm_tt_get_usermm(p->uf_entry.robj->tbo.ttm)) {
		r = -EINVAL;
		goto error_unref;
	}

	*offset = data->offset;

	return 0;

error_unref:
	amdgpu_bo_unref(&p->uf_entry.robj);
	return r;
}