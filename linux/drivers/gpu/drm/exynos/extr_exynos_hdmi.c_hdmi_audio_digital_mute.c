#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mute; } ;
struct hdmi_context {int /*<<< orphan*/  mutex; scalar_t__ powered; TYPE_1__ audio; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct hdmi_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hdmi_audio_control (struct hdmi_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi_audio_digital_mute(struct device *dev, void *data, bool mute)
{
	struct hdmi_context *hdata = dev_get_drvdata(dev);

	mutex_lock(&hdata->mutex);

	hdata->audio.mute = mute;

	if (hdata->powered)
		hdmi_audio_control(hdata);

	mutex_unlock(&hdata->mutex);

	return 0;
}