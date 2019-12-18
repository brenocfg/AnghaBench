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
struct hdmi_codec_pdata {int i2s; int spdif; int max_i2s_channels; int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;
struct cdn_dp_device {int /*<<< orphan*/  audio_pdev; } ;
typedef  int /*<<< orphan*/  codec_data ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CODEC_DRV_NAME ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_codec_ops ; 
 int /*<<< orphan*/  platform_device_register_data (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hdmi_codec_pdata*,int) ; 

__attribute__((used)) static int cdn_dp_audio_codec_init(struct cdn_dp_device *dp,
				   struct device *dev)
{
	struct hdmi_codec_pdata codec_data = {
		.i2s = 1,
		.spdif = 1,
		.ops = &audio_codec_ops,
		.max_i2s_channels = 8,
	};

	dp->audio_pdev = platform_device_register_data(
			 dev, HDMI_CODEC_DRV_NAME, PLATFORM_DEVID_AUTO,
			 &codec_data, sizeof(codec_data));

	return PTR_ERR_OR_ZERO(dp->audio_pdev);
}