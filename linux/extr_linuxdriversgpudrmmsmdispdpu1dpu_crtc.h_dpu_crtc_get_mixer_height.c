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
struct drm_display_mode {int vdisplay; } ;
struct dpu_crtc_state {int dummy; } ;
struct dpu_crtc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int dpu_crtc_get_mixer_height(struct dpu_crtc *dpu_crtc,
		struct dpu_crtc_state *cstate, struct drm_display_mode *mode)
{
	if (!dpu_crtc || !cstate || !mode)
		return 0;

	return mode->vdisplay;
}