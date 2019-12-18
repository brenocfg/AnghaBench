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
struct omap_hdmi {int audio_playing; int /*<<< orphan*/  audio_playing_lock; scalar_t__ display_enabled; int /*<<< orphan*/  cfg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct omap_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hdmi_mode_has_audio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_start_audio_stream (struct omap_hdmi*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hdmi_audio_start(struct device *dev)
{
	struct omap_hdmi *hd = dev_get_drvdata(dev);
	unsigned long flags;

	WARN_ON(!hdmi_mode_has_audio(&hd->cfg));

	spin_lock_irqsave(&hd->audio_playing_lock, flags);

	if (hd->display_enabled)
		hdmi_start_audio_stream(hd);
	hd->audio_playing = true;

	spin_unlock_irqrestore(&hd->audio_playing_lock, flags);
	return 0;
}