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
struct omap_hdmi {void (* audio_abort_cb ) (struct device*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  display_enabled; int /*<<< orphan*/  cfg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 struct omap_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hdmi_mode_has_audio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi_audio_startup(struct device *dev,
			      void (*abort_cb)(struct device *dev))
{
	struct omap_hdmi *hd = dev_get_drvdata(dev);
	int ret = 0;

	mutex_lock(&hd->lock);

	if (!hdmi_mode_has_audio(&hd->cfg) || !hd->display_enabled) {
		ret = -EPERM;
		goto out;
	}

	hd->audio_abort_cb = abort_cb;

out:
	mutex_unlock(&hd->lock);

	return ret;
}