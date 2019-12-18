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
struct gma_limit_t {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 size_t INTEL_LIMIT_I9XX_LVDS ; 
 size_t INTEL_LIMIT_I9XX_SDVO_DAC ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 scalar_t__ gma_pipe_has_type (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 struct gma_limit_t* psb_intel_limits ; 

__attribute__((used)) static const struct gma_limit_t *psb_intel_limit(struct drm_crtc *crtc,
						 int refclk)
{
	const struct gma_limit_t *limit;

	if (gma_pipe_has_type(crtc, INTEL_OUTPUT_LVDS))
		limit = &psb_intel_limits[INTEL_LIMIT_I9XX_LVDS];
	else
		limit = &psb_intel_limits[INTEL_LIMIT_I9XX_SDVO_DAC];
	return limit;
}