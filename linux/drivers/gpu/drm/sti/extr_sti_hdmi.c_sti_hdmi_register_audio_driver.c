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
struct TYPE_2__ {int enabled; } ;
struct sti_hdmi {int /*<<< orphan*/  audio_pdev; TYPE_1__ audio; } ;
struct hdmi_codec_pdata {int max_i2s_channels; int i2s; int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  codec_data ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_CODEC_DRV_NAME ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_codec_ops ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  platform_device_register_data (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hdmi_codec_pdata*,int) ; 

__attribute__((used)) static int sti_hdmi_register_audio_driver(struct device *dev,
					  struct sti_hdmi *hdmi)
{
	struct hdmi_codec_pdata codec_data = {
		.ops = &audio_codec_ops,
		.max_i2s_channels = 8,
		.i2s = 1,
	};

	DRM_DEBUG_DRIVER("\n");

	hdmi->audio.enabled = false;

	hdmi->audio_pdev = platform_device_register_data(
		dev, HDMI_CODEC_DRV_NAME, PLATFORM_DEVID_AUTO,
		&codec_data, sizeof(codec_data));

	if (IS_ERR(hdmi->audio_pdev))
		return PTR_ERR(hdmi->audio_pdev);

	DRM_INFO("%s Driver bound %s\n", HDMI_CODEC_DRV_NAME, dev_name(dev));

	return 0;
}