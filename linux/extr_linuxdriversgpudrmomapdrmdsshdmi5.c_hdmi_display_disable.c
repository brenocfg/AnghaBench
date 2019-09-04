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
struct omap_hdmi {int display_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  audio_playing_lock; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 struct omap_hdmi* dssdev_to_hdmi (struct omap_dss_device*) ; 
 int /*<<< orphan*/  hdmi_power_off_full (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_stop_audio_stream (struct omap_hdmi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hdmi_display_disable(struct omap_dss_device *dssdev)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);
	unsigned long flags;

	DSSDBG("Enter hdmi_display_disable\n");

	mutex_lock(&hdmi->lock);

	spin_lock_irqsave(&hdmi->audio_playing_lock, flags);
	hdmi_stop_audio_stream(hdmi);
	hdmi->display_enabled = false;
	spin_unlock_irqrestore(&hdmi->audio_playing_lock, flags);

	hdmi_power_off_full(hdmi);

	mutex_unlock(&hdmi->lock);
}