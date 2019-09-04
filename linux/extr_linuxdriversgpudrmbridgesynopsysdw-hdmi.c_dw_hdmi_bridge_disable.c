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
struct dw_hdmi {int disabled; int /*<<< orphan*/  mutex; } ;
struct drm_bridge {struct dw_hdmi* driver_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_hdmi_update_phy_mask (struct dw_hdmi*) ; 
 int /*<<< orphan*/  dw_hdmi_update_power (struct dw_hdmi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dw_hdmi_bridge_disable(struct drm_bridge *bridge)
{
	struct dw_hdmi *hdmi = bridge->driver_private;

	mutex_lock(&hdmi->mutex);
	hdmi->disabled = true;
	dw_hdmi_update_power(hdmi);
	dw_hdmi_update_phy_mask(hdmi);
	mutex_unlock(&hdmi->mutex);
}