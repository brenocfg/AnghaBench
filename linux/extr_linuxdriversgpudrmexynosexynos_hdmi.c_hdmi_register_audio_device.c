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
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct hdmi_context {TYPE_1__ audio; int /*<<< orphan*/  dev; } ;
struct hdmi_codec_pdata {int max_i2s_channels; int i2s; int /*<<< orphan*/ * ops; } ;
typedef  int /*<<< orphan*/  codec_data ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CODEC_DRV_NAME ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_codec_ops ; 
 int /*<<< orphan*/  platform_device_register_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hdmi_codec_pdata*,int) ; 

__attribute__((used)) static int hdmi_register_audio_device(struct hdmi_context *hdata)
{
	struct hdmi_codec_pdata codec_data = {
		.ops = &audio_codec_ops,
		.max_i2s_channels = 6,
		.i2s = 1,
	};

	hdata->audio.pdev = platform_device_register_data(
		hdata->dev, HDMI_CODEC_DRV_NAME, PLATFORM_DEVID_AUTO,
		&codec_data, sizeof(codec_data));

	return PTR_ERR_OR_ZERO(hdata->audio.pdev);
}