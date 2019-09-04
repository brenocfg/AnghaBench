#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct radeon_ib {int gpu_addr; int length_dw; int /*<<< orphan*/  fence; void** ptr; } ;
struct radeon_fence {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 void* cpu_to_le32 (int) ; 
 struct radeon_fence* radeon_fence_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ib_free (struct radeon_device*,struct radeon_ib*) ; 
 int radeon_ib_get (struct radeon_device*,int,struct radeon_ib*,int /*<<< orphan*/ *,unsigned int const) ; 
 int radeon_ib_schedule (struct radeon_device*,struct radeon_ib*,int /*<<< orphan*/ *,int) ; 
 int upper_32_bits (int) ; 

int radeon_vce_get_destroy_msg(struct radeon_device *rdev, int ring,
			       uint32_t handle, struct radeon_fence **fence)
{
	const unsigned ib_size_dw = 1024;
	struct radeon_ib ib;
	uint64_t dummy;
	int i, r;

	r = radeon_ib_get(rdev, ring, &ib, NULL, ib_size_dw * 4);
	if (r) {
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		return r;
	}

	dummy = ib.gpu_addr + 1024;

	/* stitch together an VCE destroy msg */
	ib.length_dw = 0;
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x0000000c); /* len */
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000001); /* session cmd */
	ib.ptr[ib.length_dw++] = cpu_to_le32(handle);

	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000014); /* len */
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x05000005); /* feedback buffer */
	ib.ptr[ib.length_dw++] = cpu_to_le32(upper_32_bits(dummy));
	ib.ptr[ib.length_dw++] = cpu_to_le32(dummy);
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000001);

	ib.ptr[ib.length_dw++] = cpu_to_le32(0x00000008); /* len */
	ib.ptr[ib.length_dw++] = cpu_to_le32(0x02000001); /* destroy cmd */

	for (i = ib.length_dw; i < ib_size_dw; ++i)
		ib.ptr[i] = cpu_to_le32(0x0);

	r = radeon_ib_schedule(rdev, &ib, NULL, false);
	if (r) {
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);
	}

	if (fence)
		*fence = radeon_fence_ref(ib.fence);

	radeon_ib_free(rdev, &ib);

	return r;
}