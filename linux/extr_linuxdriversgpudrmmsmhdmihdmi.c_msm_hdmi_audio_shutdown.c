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
struct hdmi {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  msm_hdmi_audio_info_setup (struct hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_hdmi_audio_shutdown(struct device *dev, void *data)
{
	struct hdmi *hdmi = dev_get_drvdata(dev);

	msm_hdmi_audio_info_setup(hdmi, 0, 0, 0, 0, 0);
}