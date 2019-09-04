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
typedef  scalar_t__ u32 ;
struct drm_display_mode {scalar_t__ crtc_hdisplay; scalar_t__ crtc_vdisplay; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {scalar_t__ pipe_src_h; scalar_t__ pipe_src_w; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ PFIT_ENABLE ; 
 scalar_t__ PFIT_SCALING_AUTO ; 
 scalar_t__ PFIT_SCALING_LETTER ; 
 scalar_t__ PFIT_SCALING_PILLAR ; 

__attribute__((used)) static void i965_scale_aspect(struct intel_crtc_state *pipe_config,
			      u32 *pfit_control)
{
	const struct drm_display_mode *adjusted_mode = &pipe_config->base.adjusted_mode;
	u32 scaled_width = adjusted_mode->crtc_hdisplay *
		pipe_config->pipe_src_h;
	u32 scaled_height = pipe_config->pipe_src_w *
		adjusted_mode->crtc_vdisplay;

	/* 965+ is easy, it does everything in hw */
	if (scaled_width > scaled_height)
		*pfit_control |= PFIT_ENABLE |
			PFIT_SCALING_PILLAR;
	else if (scaled_width < scaled_height)
		*pfit_control |= PFIT_ENABLE |
			PFIT_SCALING_LETTER;
	else if (adjusted_mode->crtc_hdisplay != pipe_config->pipe_src_w)
		*pfit_control |= PFIT_ENABLE | PFIT_SCALING_AUTO;
}