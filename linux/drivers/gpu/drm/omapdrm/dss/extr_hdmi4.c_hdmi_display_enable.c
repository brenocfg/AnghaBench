#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pixelclock; } ;
struct TYPE_5__ {TYPE_1__ vm; } ;
struct omap_hdmi {int audio_configured; int display_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  audio_playing_lock; scalar_t__ audio_playing; TYPE_3__* pdev; int /*<<< orphan*/  (* audio_abort_cb ) (int /*<<< orphan*/ *) ;TYPE_2__ cfg; int /*<<< orphan*/  audio_config; int /*<<< orphan*/  wp; int /*<<< orphan*/  core; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 struct omap_hdmi* dssdev_to_hdmi (struct omap_dss_device*) ; 
 int hdmi4_audio_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hdmi_power_on_full (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_start_audio_stream (struct omap_hdmi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_display_enable(struct omap_dss_device *dssdev)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);
	unsigned long flags;
	int r;

	DSSDBG("ENTER hdmi_display_enable\n");

	mutex_lock(&hdmi->lock);

	r = hdmi_power_on_full(hdmi);
	if (r) {
		DSSERR("failed to power on device\n");
		goto done;
	}

	if (hdmi->audio_configured) {
		r = hdmi4_audio_config(&hdmi->core, &hdmi->wp,
				       &hdmi->audio_config,
				       hdmi->cfg.vm.pixelclock);
		if (r) {
			DSSERR("Error restoring audio configuration: %d", r);
			hdmi->audio_abort_cb(&hdmi->pdev->dev);
			hdmi->audio_configured = false;
		}
	}

	spin_lock_irqsave(&hdmi->audio_playing_lock, flags);
	if (hdmi->audio_configured && hdmi->audio_playing)
		hdmi_start_audio_stream(hdmi);
	hdmi->display_enabled = true;
	spin_unlock_irqrestore(&hdmi->audio_playing_lock, flags);

done:
	mutex_unlock(&hdmi->lock);
}