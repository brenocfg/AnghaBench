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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int num_mec; int num_pipe_per_mec; int /*<<< orphan*/  hpd_eop_obj; int /*<<< orphan*/  hpd_eop_gpu_addr; int /*<<< orphan*/  queue_bitmap; } ;
struct TYPE_4__ {TYPE_1__ mec; } ;
struct amdgpu_device {TYPE_2__ gfx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  AMDGPU_MAX_COMPUTE_QUEUES ; 
 int GFX7_MEC_HPD_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_reserved (struct amdgpu_device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gfx_compute_queue_acquire (struct amdgpu_device*) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_mec_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int gfx_v7_0_mec_init(struct amdgpu_device *adev)
{
	int r;
	u32 *hpd;
	size_t mec_hpd_size;

	bitmap_zero(adev->gfx.mec.queue_bitmap, AMDGPU_MAX_COMPUTE_QUEUES);

	/* take ownership of the relevant compute queues */
	amdgpu_gfx_compute_queue_acquire(adev);

	/* allocate space for ALL pipes (even the ones we don't own) */
	mec_hpd_size = adev->gfx.mec.num_mec * adev->gfx.mec.num_pipe_per_mec
		* GFX7_MEC_HPD_SIZE * 2;

	r = amdgpu_bo_create_reserved(adev, mec_hpd_size, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &adev->gfx.mec.hpd_eop_obj,
				      &adev->gfx.mec.hpd_eop_gpu_addr,
				      (void **)&hpd);
	if (r) {
		dev_warn(adev->dev, "(%d) create, pin or map of HDP EOP bo failed\n", r);
		gfx_v7_0_mec_fini(adev);
		return r;
	}

	/* clear memory.  Not sure if this is required or not */
	memset(hpd, 0, mec_hpd_size);

	amdgpu_bo_kunmap(adev->gfx.mec.hpd_eop_obj);
	amdgpu_bo_unreserve(adev->gfx.mec.hpd_eop_obj);

	return 0;
}