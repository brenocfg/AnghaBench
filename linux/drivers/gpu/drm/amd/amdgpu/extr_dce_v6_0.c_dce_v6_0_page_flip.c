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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct drm_framebuffer {int* pitches; TYPE_4__* format; } ;
struct TYPE_5__ {struct amdgpu_crtc** crtcs; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_7__ {TYPE_2__* primary; } ;
struct amdgpu_crtc {scalar_t__ crtc_offset; TYPE_3__ base; } ;
struct TYPE_8__ {int* cpp; } ;
struct TYPE_6__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int GRPH_FLIP_CONTROL__GRPH_SURFACE_UPDATE_H_RETRACE_EN_MASK ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ mmGRPH_FLIP_CONTROL ; 
 scalar_t__ mmGRPH_PITCH ; 
 scalar_t__ mmGRPH_PRIMARY_SURFACE_ADDRESS ; 
 scalar_t__ mmGRPH_PRIMARY_SURFACE_ADDRESS_HIGH ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void dce_v6_0_page_flip(struct amdgpu_device *adev,
			       int crtc_id, u64 crtc_base, bool async)
{
	struct amdgpu_crtc *amdgpu_crtc = adev->mode_info.crtcs[crtc_id];
	struct drm_framebuffer *fb = amdgpu_crtc->base.primary->fb;

	/* flip at hsync for async, default is vsync */
	WREG32(mmGRPH_FLIP_CONTROL + amdgpu_crtc->crtc_offset, async ?
	       GRPH_FLIP_CONTROL__GRPH_SURFACE_UPDATE_H_RETRACE_EN_MASK : 0);
	/* update pitch */
	WREG32(mmGRPH_PITCH + amdgpu_crtc->crtc_offset,
	       fb->pitches[0] / fb->format->cpp[0]);
	/* update the scanout addresses */
	WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS_HIGH + amdgpu_crtc->crtc_offset,
	       upper_32_bits(crtc_base));
	WREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset,
	       (u32)crtc_base);

	/* post the write */
	RREG32(mmGRPH_PRIMARY_SURFACE_ADDRESS + amdgpu_crtc->crtc_offset);
}