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
struct dw_hdmi {int /*<<< orphan*/  mutex; int /*<<< orphan*/  previous_mode; } ;
struct drm_display_mode {int dummy; } ;
struct drm_bridge {struct dw_hdmi* driver_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct drm_display_mode const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dw_hdmi_bridge_mode_set(struct drm_bridge *bridge,
				    const struct drm_display_mode *orig_mode,
				    const struct drm_display_mode *mode)
{
	struct dw_hdmi *hdmi = bridge->driver_private;

	mutex_lock(&hdmi->mutex);

	/* Store the display mode for plugin/DKMS poweron events */
	memcpy(&hdmi->previous_mode, mode, sizeof(hdmi->previous_mode));

	mutex_unlock(&hdmi->mutex);
}