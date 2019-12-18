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
struct hdmi_avi_infoframe {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_bridge {int dummy; } ;
struct anx78xx {int /*<<< orphan*/  lock; int /*<<< orphan*/  connector; int /*<<< orphan*/  powered; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int anx78xx_send_video_infoframe (struct anx78xx*,struct hdmi_avi_infoframe*) ; 
 struct anx78xx* bridge_to_anx78xx (struct drm_bridge*) ; 
 int drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void anx78xx_bridge_mode_set(struct drm_bridge *bridge,
				const struct drm_display_mode *mode,
				const struct drm_display_mode *adjusted_mode)
{
	struct anx78xx *anx78xx = bridge_to_anx78xx(bridge);
	struct hdmi_avi_infoframe frame;
	int err;

	if (WARN_ON(!anx78xx->powered))
		return;

	mutex_lock(&anx78xx->lock);

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       &anx78xx->connector,
						       adjusted_mode);
	if (err) {
		DRM_ERROR("Failed to setup AVI infoframe: %d\n", err);
		goto unlock;
	}

	err = anx78xx_send_video_infoframe(anx78xx, &frame);
	if (err)
		DRM_ERROR("Failed to send AVI infoframe: %d\n", err);

unlock:
	mutex_unlock(&anx78xx->lock);
}