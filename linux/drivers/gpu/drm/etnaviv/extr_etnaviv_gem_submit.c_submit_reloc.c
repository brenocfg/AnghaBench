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
struct etnaviv_gem_submit_bo {TYPE_3__* mapping; TYPE_2__* obj; } ;
struct etnaviv_gem_submit {int flags; } ;
struct drm_etnaviv_gem_submit_reloc {int submit_offset; int reloc_offset; int /*<<< orphan*/  reloc_idx; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {scalar_t__ iova; } ;
struct TYPE_4__ {int size; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int ETNA_SUBMIT_SOFTPIN ; 
 int submit_bo (struct etnaviv_gem_submit*,int /*<<< orphan*/ ,struct etnaviv_gem_submit_bo**) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int submit_reloc(struct etnaviv_gem_submit *submit, void *stream,
		u32 size, const struct drm_etnaviv_gem_submit_reloc *relocs,
		u32 nr_relocs)
{
	u32 i, last_offset = 0;
	u32 *ptr = stream;
	int ret;

	/* Submits using softpin don't blend with relocs */
	if ((submit->flags & ETNA_SUBMIT_SOFTPIN) && nr_relocs != 0)
		return -EINVAL;

	for (i = 0; i < nr_relocs; i++) {
		const struct drm_etnaviv_gem_submit_reloc *r = relocs + i;
		struct etnaviv_gem_submit_bo *bo;
		u32 off;

		if (unlikely(r->flags)) {
			DRM_ERROR("invalid reloc flags\n");
			return -EINVAL;
		}

		if (r->submit_offset % 4) {
			DRM_ERROR("non-aligned reloc offset: %u\n",
				  r->submit_offset);
			return -EINVAL;
		}

		/* offset in dwords: */
		off = r->submit_offset / 4;

		if ((off >= size ) ||
				(off < last_offset)) {
			DRM_ERROR("invalid offset %u at reloc %u\n", off, i);
			return -EINVAL;
		}

		ret = submit_bo(submit, r->reloc_idx, &bo);
		if (ret)
			return ret;

		if (r->reloc_offset > bo->obj->base.size - sizeof(*ptr)) {
			DRM_ERROR("relocation %u outside object\n", i);
			return -EINVAL;
		}

		ptr[off] = bo->mapping->iova + r->reloc_offset;

		last_offset = off;
	}

	return 0;
}