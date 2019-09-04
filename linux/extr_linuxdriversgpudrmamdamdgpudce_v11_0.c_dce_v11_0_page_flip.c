#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct amdgpu_crtc** crtcs; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct amdgpu_crtc {scalar_t__ crtc_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_FLIP_CONTROL ; 
 int /*<<< orphan*/  GRPH_SURFACE_UPDATE_IMMEDIATE_EN ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ mmGRPH_FLIP_CONTROL ; 
 scalar_t__ mmGRPH_PRIMARY_SURFACE_ADDRESS ; 
 scalar_t__ mmGRPH_PRIMARY_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce_v11_0_page_flip(struct amdgpu_device *adev,
				int crtc_id, u64 crtc_base, bool async)
{
	struct amdgpu_crtc *amdgpu_crtc = adev->mode_info.crtcs[crtc_id];
	u32 tmp;

	/* flip immediate for async, default is vsync */
	tmp = RREG32(mmGRPH_FLIP_CONTROL + amdgpu_crtc->crtc_offset);
	tmp = REG_SET_FIELD(tmp, GRPH_FLIP_CONTROL,
			    GRPH_SURFACE_UPDATE_IMMEDIATE_EN, async ? 1 : 0);
	WREG32(mmGRPH_FLIP_CONTROL + amdgpu_crtc->crtc_offset, tmp);
	/* update the scanout addresses */
	WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS_HIGH + amdgpu_crtc->crtc_offset,
	       upper_32_bits(crtc_base));
	/* writing to the low address triggers the update */
	WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset,
	       lower_32_bits(crtc_base));
	/* post the write */
	RREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset);
}