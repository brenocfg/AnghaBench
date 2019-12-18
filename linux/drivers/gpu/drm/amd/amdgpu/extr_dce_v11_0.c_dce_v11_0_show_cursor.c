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
typedef  int /*<<< orphan*/  u32 ;
struct drm_crtc {TYPE_1__* dev; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {scalar_t__ crtc_offset; int /*<<< orphan*/  cursor_addr; } ;
struct TYPE_2__ {struct amdgpu_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_EN ; 
 int /*<<< orphan*/  CURSOR_MODE ; 
 int /*<<< orphan*/  CUR_CONTROL ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_IDX (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_IDX (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ mmCUR_CONTROL ; 
 scalar_t__ mmCUR_SURFACE_ADDRESS ; 
 scalar_t__ mmCUR_SURFACE_ADDRESS_HIGH ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce_v11_0_show_cursor(struct drm_crtc *crtc)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct amdgpu_device *adev = crtc->dev->dev_private;
	u32 tmp;

	WREG32(mmCUR_SURFACE_ADDRESS_HIGH + amdgpu_crtc->crtc_offset,
	       upper_32_bits(amdgpu_crtc->cursor_addr));
	WREG32(mmCUR_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset,
	       lower_32_bits(amdgpu_crtc->cursor_addr));

	tmp = RREG32_IDX(mmCUR_CONTROL + amdgpu_crtc->crtc_offset);
	tmp = REG_SET_FIELD(tmp, CUR_CONTROL, CURSOR_EN, 1);
	tmp = REG_SET_FIELD(tmp, CUR_CONTROL, CURSOR_MODE, 2);
	WREG32_IDX(mmCUR_CONTROL + amdgpu_crtc->crtc_offset, tmp);
}