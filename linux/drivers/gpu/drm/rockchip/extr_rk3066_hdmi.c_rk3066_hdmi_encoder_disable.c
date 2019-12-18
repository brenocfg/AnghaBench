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
struct rk3066_hdmi {int /*<<< orphan*/  dev; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HDMI_AUDIO_CP_LOGIC_RESET ; 
 int /*<<< orphan*/  HDMI_AUDIO_CP_LOGIC_RESET_MASK ; 
 int /*<<< orphan*/  HDMI_SYS_POWER_MODE_A ; 
 scalar_t__ HDMI_SYS_POWER_MODE_E ; 
 int /*<<< orphan*/  HDMI_VIDEO_AUDIO_DISABLE_MASK ; 
 int /*<<< orphan*/  HDMI_VIDEO_CTRL2 ; 
 int /*<<< orphan*/  hdmi_modb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rk3066_hdmi_get_power_mode (struct rk3066_hdmi*) ; 
 int /*<<< orphan*/  rk3066_hdmi_set_power_mode (struct rk3066_hdmi*,int /*<<< orphan*/ ) ; 
 struct rk3066_hdmi* to_rk3066_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void rk3066_hdmi_encoder_disable(struct drm_encoder *encoder)
{
	struct rk3066_hdmi *hdmi = to_rk3066_hdmi(encoder);

	DRM_DEV_DEBUG(hdmi->dev, "hdmi encoder disable\n");

	if (rk3066_hdmi_get_power_mode(hdmi) == HDMI_SYS_POWER_MODE_E) {
		hdmi_writeb(hdmi, HDMI_VIDEO_CTRL2,
			    HDMI_VIDEO_AUDIO_DISABLE_MASK);
		hdmi_modb(hdmi, HDMI_VIDEO_CTRL2,
			  HDMI_AUDIO_CP_LOGIC_RESET_MASK,
			  HDMI_AUDIO_CP_LOGIC_RESET);
		usleep_range(500, 510);
	}
	rk3066_hdmi_set_power_mode(hdmi, HDMI_SYS_POWER_MODE_A);
}