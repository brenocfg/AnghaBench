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
typedef  int u32 ;
struct gma_crtc {scalar_t__ pipe; } ;
struct drm_encoder {struct drm_crtc* crtc; struct drm_device* dev; } ;
struct drm_display_mode {int flags; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int ADPA ; 
 int ADPA_HSYNC_ACTIVE_HIGH ; 
 int ADPA_PIPE_A_SELECT ; 
 int ADPA_PIPE_B_SELECT ; 
 int ADPA_VSYNC_ACTIVE_HIGH ; 
 int DPLL_A_MD ; 
 int DPLL_B_MD ; 
 int DPLL_MD_UDI_MULTIPLIER_MASK ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int REG_READ (int) ; 
 int /*<<< orphan*/  REG_WRITE (int,int) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void cdv_intel_crt_mode_set(struct drm_encoder *encoder,
			       struct drm_display_mode *mode,
			       struct drm_display_mode *adjusted_mode)
{

	struct drm_device *dev = encoder->dev;
	struct drm_crtc *crtc = encoder->crtc;
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);
	int dpll_md_reg;
	u32 adpa, dpll_md;
	u32 adpa_reg;

	if (gma_crtc->pipe == 0)
		dpll_md_reg = DPLL_A_MD;
	else
		dpll_md_reg = DPLL_B_MD;

	adpa_reg = ADPA;

	/*
	 * Disable separate mode multiplier used when cloning SDVO to CRT
	 * XXX this needs to be adjusted when we really are cloning
	 */
	{
		dpll_md = REG_READ(dpll_md_reg);
		REG_WRITE(dpll_md_reg,
			   dpll_md & ~DPLL_MD_UDI_MULTIPLIER_MASK);
	}

	adpa = 0;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		adpa |= ADPA_HSYNC_ACTIVE_HIGH;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		adpa |= ADPA_VSYNC_ACTIVE_HIGH;

	if (gma_crtc->pipe == 0)
		adpa |= ADPA_PIPE_A_SELECT;
	else
		adpa |= ADPA_PIPE_B_SELECT;

	REG_WRITE(adpa_reg, adpa);
}