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
struct drm_crtc {TYPE_1__* dev; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {scalar_t__ crtc_offset; int /*<<< orphan*/  cursor_addr; } ;
struct TYPE_2__ {struct amdgpu_device* dev_private; } ;

/* Variables and functions */
 int CURSOR_24_8_PRE_MULT ; 
 int CURSOR_URGENT_1_2 ; 
 int CUR_CONTROL__CURSOR_EN_MASK ; 
 int CUR_CONTROL__CURSOR_MODE__SHIFT ; 
 int CUR_CONTROL__CURSOR_URGENT_CONTROL__SHIFT ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_IDX (scalar_t__,int) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ mmCUR_CONTROL ; 
 scalar_t__ mmCUR_SURFACE_ADDRESS ; 
 scalar_t__ mmCUR_SURFACE_ADDRESS_HIGH ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce_v8_0_show_cursor(struct drm_crtc *crtc)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	struct amdgpu_device *adev = crtc->dev->dev_private;

	WREG32(mmCUR_SURFACE_ADDRESS_HIGH + amdgpu_crtc->crtc_offset,
	       upper_32_bits(amdgpu_crtc->cursor_addr));
	WREG32(mmCUR_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset,
	       lower_32_bits(amdgpu_crtc->cursor_addr));

	WREG32_IDX(mmCUR_CONTROL + amdgpu_crtc->crtc_offset,
		   CUR_CONTROL__CURSOR_EN_MASK |
		   (CURSOR_24_8_PRE_MULT << CUR_CONTROL__CURSOR_MODE__SHIFT) |
		   (CURSOR_URGENT_1_2 << CUR_CONTROL__CURSOR_URGENT_CONTROL__SHIFT));
}