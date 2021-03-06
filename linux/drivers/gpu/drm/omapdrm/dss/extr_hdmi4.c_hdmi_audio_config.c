#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_dss_audio {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pixelclock; } ;
struct TYPE_4__ {TYPE_1__ vm; } ;
struct omap_hdmi {int audio_configured; int /*<<< orphan*/  lock; struct omap_dss_audio audio_config; TYPE_2__ cfg; int /*<<< orphan*/  wp; int /*<<< orphan*/  core; scalar_t__ display_enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct omap_hdmi* dev_get_drvdata (struct device*) ; 
 int hdmi4_audio_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct omap_dss_audio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi_audio_config(struct device *dev,
			     struct omap_dss_audio *dss_audio)
{
	struct omap_hdmi *hd = dev_get_drvdata(dev);
	int ret = 0;

	mutex_lock(&hd->lock);

	if (hd->display_enabled) {
		ret = hdmi4_audio_config(&hd->core, &hd->wp, dss_audio,
					 hd->cfg.vm.pixelclock);
		if (ret)
			goto out;
	}

	hd->audio_configured = true;
	hd->audio_config = *dss_audio;
out:
	mutex_unlock(&hd->lock);

	return ret;
}