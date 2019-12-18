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
struct omap_hdmi {void (* audio_abort_cb ) (struct device*) ;int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct omap_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi_audio_startup(struct device *dev,
			      void (*abort_cb)(struct device *dev))
{
	struct omap_hdmi *hd = dev_get_drvdata(dev);

	mutex_lock(&hd->lock);

	WARN_ON(hd->audio_abort_cb != NULL);

	hd->audio_abort_cb = abort_cb;

	mutex_unlock(&hd->lock);

	return 0;
}