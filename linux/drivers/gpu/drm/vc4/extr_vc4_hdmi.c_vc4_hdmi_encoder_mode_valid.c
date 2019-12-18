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
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int clock; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int HSM_CLOCK_FREQ ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_OK ; 

__attribute__((used)) static enum drm_mode_status
vc4_hdmi_encoder_mode_valid(struct drm_encoder *crtc,
			    const struct drm_display_mode *mode)
{
	/* HSM clock must be 108% of the pixel clock.  Additionally,
	 * the AXI clock needs to be at least 25% of pixel clock, but
	 * HSM ends up being the limiting factor.
	 */
	if (mode->clock > HSM_CLOCK_FREQ / (1000 * 108 / 100))
		return MODE_CLOCK_HIGH;

	return MODE_OK;
}