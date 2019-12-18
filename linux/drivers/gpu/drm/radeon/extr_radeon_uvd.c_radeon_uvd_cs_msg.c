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
struct radeon_fence {int dummy; } ;
struct radeon_cs_parser {TYPE_4__* rdev; int /*<<< orphan*/  filp; } ;
struct TYPE_5__ {int /*<<< orphan*/  resv; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct radeon_bo {TYPE_2__ tbo; } ;
struct dma_fence {int dummy; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_7__ {int max_handles; unsigned int* img_size; int /*<<< orphan*/ * handles; int /*<<< orphan*/ * filp; } ;
struct TYPE_8__ {TYPE_3__ uvd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct dma_fence* dma_resv_get_excl (int /*<<< orphan*/ ) ; 
 int radeon_bo_kmap (struct radeon_bo*,void**) ; 
 int /*<<< orphan*/  radeon_bo_kunmap (struct radeon_bo*) ; 
 int radeon_fence_wait (struct radeon_fence*,int) ; 
 int radeon_uvd_cs_msg_decode (scalar_t__*,unsigned int*) ; 
 int radeon_uvd_validate_codec (struct radeon_cs_parser*,scalar_t__) ; 

__attribute__((used)) static int radeon_uvd_cs_msg(struct radeon_cs_parser *p, struct radeon_bo *bo,
			     unsigned offset, unsigned buf_sizes[])
{
	int32_t *msg, msg_type, handle;
	unsigned img_size = 0;
	struct dma_fence *f;
	void *ptr;

	int i, r;

	if (offset & 0x3F) {
		DRM_ERROR("UVD messages must be 64 byte aligned!\n");
		return -EINVAL;
	}

	f = dma_resv_get_excl(bo->tbo.base.resv);
	if (f) {
		r = radeon_fence_wait((struct radeon_fence *)f, false);
		if (r) {
			DRM_ERROR("Failed waiting for UVD message (%d)!\n", r);
			return r;
		}
	}

	r = radeon_bo_kmap(bo, &ptr);
	if (r) {
		DRM_ERROR("Failed mapping the UVD message (%d)!\n", r);
		return r;
	}

	msg = ptr + offset;

	msg_type = msg[1];
	handle = msg[2];

	if (handle == 0) {
		DRM_ERROR("Invalid UVD handle!\n");
		return -EINVAL;
	}

	switch (msg_type) {
	case 0:
		/* it's a create msg, calc image size (width * height) */
		img_size = msg[7] * msg[8];

		r = radeon_uvd_validate_codec(p, msg[4]);
		radeon_bo_kunmap(bo);
		if (r)
			return r;

		/* try to alloc a new handle */
		for (i = 0; i < p->rdev->uvd.max_handles; ++i) {
			if (atomic_read(&p->rdev->uvd.handles[i]) == handle) {
				DRM_ERROR("Handle 0x%x already in use!\n", handle);
				return -EINVAL;
			}

			if (!atomic_cmpxchg(&p->rdev->uvd.handles[i], 0, handle)) {
				p->rdev->uvd.filp[i] = p->filp;
				p->rdev->uvd.img_size[i] = img_size;
				return 0;
			}
		}

		DRM_ERROR("No more free UVD handles!\n");
		return -EINVAL;

	case 1:
		/* it's a decode msg, validate codec and calc buffer sizes */
		r = radeon_uvd_validate_codec(p, msg[4]);
		if (!r)
			r = radeon_uvd_cs_msg_decode(msg, buf_sizes);
		radeon_bo_kunmap(bo);
		if (r)
			return r;

		/* validate the handle */
		for (i = 0; i < p->rdev->uvd.max_handles; ++i) {
			if (atomic_read(&p->rdev->uvd.handles[i]) == handle) {
				if (p->rdev->uvd.filp[i] != p->filp) {
					DRM_ERROR("UVD handle collision detected!\n");
					return -EINVAL;
				}
				return 0;
			}
		}

		DRM_ERROR("Invalid UVD handle 0x%x!\n", handle);
		return -ENOENT;

	case 2:
		/* it's a destroy msg, free the handle */
		for (i = 0; i < p->rdev->uvd.max_handles; ++i)
			atomic_cmpxchg(&p->rdev->uvd.handles[i], handle, 0);
		radeon_bo_kunmap(bo);
		return 0;

	default:

		DRM_ERROR("Illegal UVD message type (%d)!\n", msg_type);
		return -EINVAL;
	}

	BUG();
	return -EINVAL;
}