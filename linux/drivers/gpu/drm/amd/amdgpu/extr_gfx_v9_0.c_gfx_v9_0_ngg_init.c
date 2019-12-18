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
struct TYPE_5__ {int init; int /*<<< orphan*/ * buf; scalar_t__ gds_reserve_addr; scalar_t__ gds_reserve_size; } ;
struct TYPE_6__ {TYPE_2__ ngg; } ;
struct TYPE_4__ {int /*<<< orphan*/  gds_size; } ;
struct amdgpu_device {TYPE_3__ gfx; int /*<<< orphan*/  dev; TYPE_1__ gds; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int) ; 
 int /*<<< orphan*/  GC ; 
 size_t NGG_CNTL ; 
 size_t NGG_PARAM ; 
 size_t NGG_POS ; 
 size_t NGG_PRIM ; 
 scalar_t__ RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_cntl_sb_buf_per_se ; 
 int /*<<< orphan*/  amdgpu_ngg ; 
 scalar_t__ amdgpu_param_buf_per_se ; 
 scalar_t__ amdgpu_pos_buf_per_se ; 
 scalar_t__ amdgpu_prim_buf_per_se ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gfx_v9_0_ngg_create_buf (struct amdgpu_device*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  gfx_v9_0_ngg_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmGDS_VMID0_BASE ; 
 int /*<<< orphan*/  mmGDS_VMID0_SIZE ; 

__attribute__((used)) static int gfx_v9_0_ngg_init(struct amdgpu_device *adev)
{
	int r;

	if (!amdgpu_ngg || adev->gfx.ngg.init == true)
		return 0;

	/* GDS reserve memory: 64 bytes alignment */
	adev->gfx.ngg.gds_reserve_size = ALIGN(5 * 4, 0x40);
	adev->gds.gds_size -= adev->gfx.ngg.gds_reserve_size;
	adev->gfx.ngg.gds_reserve_addr = RREG32_SOC15(GC, 0, mmGDS_VMID0_BASE);
	adev->gfx.ngg.gds_reserve_addr += RREG32_SOC15(GC, 0, mmGDS_VMID0_SIZE);

	/* Primitive Buffer */
	r = gfx_v9_0_ngg_create_buf(adev, &adev->gfx.ngg.buf[NGG_PRIM],
				    amdgpu_prim_buf_per_se,
				    64 * 1024);
	if (r) {
		dev_err(adev->dev, "Failed to create Primitive Buffer\n");
		goto err;
	}

	/* Position Buffer */
	r = gfx_v9_0_ngg_create_buf(adev, &adev->gfx.ngg.buf[NGG_POS],
				    amdgpu_pos_buf_per_se,
				    256 * 1024);
	if (r) {
		dev_err(adev->dev, "Failed to create Position Buffer\n");
		goto err;
	}

	/* Control Sideband */
	r = gfx_v9_0_ngg_create_buf(adev, &adev->gfx.ngg.buf[NGG_CNTL],
				    amdgpu_cntl_sb_buf_per_se,
				    256);
	if (r) {
		dev_err(adev->dev, "Failed to create Control Sideband Buffer\n");
		goto err;
	}

	/* Parameter Cache, not created by default */
	if (amdgpu_param_buf_per_se <= 0)
		goto out;

	r = gfx_v9_0_ngg_create_buf(adev, &adev->gfx.ngg.buf[NGG_PARAM],
				    amdgpu_param_buf_per_se,
				    512 * 1024);
	if (r) {
		dev_err(adev->dev, "Failed to create Parameter Cache\n");
		goto err;
	}

out:
	adev->gfx.ngg.init = true;
	return 0;
err:
	gfx_v9_0_ngg_fini(adev);
	return r;
}