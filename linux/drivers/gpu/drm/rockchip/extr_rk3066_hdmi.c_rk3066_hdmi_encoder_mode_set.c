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
struct rk3066_hdmi {int /*<<< orphan*/  previous_mode; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct drm_display_mode*,int) ; 
 struct rk3066_hdmi* to_rk3066_hdmi (struct drm_encoder*) ; 

__attribute__((used)) static void
rk3066_hdmi_encoder_mode_set(struct drm_encoder *encoder,
			     struct drm_display_mode *mode,
			     struct drm_display_mode *adj_mode)
{
	struct rk3066_hdmi *hdmi = to_rk3066_hdmi(encoder);

	/* Store the display mode for plugin/DPMS poweron events. */
	memcpy(&hdmi->previous_mode, adj_mode, sizeof(hdmi->previous_mode));
}