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
struct inno_hdmi {int /*<<< orphan*/  previous_mode; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inno_hdmi_setup (struct inno_hdmi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct drm_display_mode*,int) ; 
 struct inno_hdmi* to_inno_hdmi (struct drm_encoder*) ; 

__attribute__((used)) static void inno_hdmi_encoder_mode_set(struct drm_encoder *encoder,
				       struct drm_display_mode *mode,
				       struct drm_display_mode *adj_mode)
{
	struct inno_hdmi *hdmi = to_inno_hdmi(encoder);

	inno_hdmi_setup(hdmi, adj_mode);

	/* Store the display mode for plugin/DPMS poweron events */
	memcpy(&hdmi->previous_mode, adj_mode, sizeof(hdmi->previous_mode));
}