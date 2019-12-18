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
struct drm_display_mode {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  crtc_vtotal; int /*<<< orphan*/  crtc_vsync_end; int /*<<< orphan*/  crtc_vsync_start; int /*<<< orphan*/  crtc_vdisplay; int /*<<< orphan*/  crtc_htotal; int /*<<< orphan*/  crtc_hsync_end; int /*<<< orphan*/  crtc_hsync_start; int /*<<< orphan*/  crtc_hdisplay; int /*<<< orphan*/  crtc_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dump_crtc_timings(const struct drm_display_mode *mode)
{
	DRM_DEBUG_KMS("crtc timings: %d %d %d %d %d %d %d %d %d, "
		      "type: 0x%x flags: 0x%x\n",
		      mode->crtc_clock,
		      mode->crtc_hdisplay, mode->crtc_hsync_start,
		      mode->crtc_hsync_end, mode->crtc_htotal,
		      mode->crtc_vdisplay, mode->crtc_vsync_start,
		      mode->crtc_vsync_end, mode->crtc_vtotal,
		      mode->type, mode->flags);
}