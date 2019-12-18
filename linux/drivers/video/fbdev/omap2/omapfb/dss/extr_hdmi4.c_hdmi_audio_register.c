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
struct omap_hdmi_audio_pdata {int version; int /*<<< orphan*/ * ops; int /*<<< orphan*/  audio_dma_addr; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  pdata ;
struct TYPE_2__ {int /*<<< orphan*/  audio_pdev; int /*<<< orphan*/  wp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 TYPE_1__ hdmi ; 
 int /*<<< orphan*/  hdmi_audio_ops ; 
 int /*<<< orphan*/  hdmi_wp_get_audio_dma_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_register_data (struct device*,char*,int /*<<< orphan*/ ,struct omap_hdmi_audio_pdata*,int) ; 

__attribute__((used)) static int hdmi_audio_register(struct device *dev)
{
	struct omap_hdmi_audio_pdata pdata = {
		.dev = dev,
		.version = 4,
		.audio_dma_addr = hdmi_wp_get_audio_dma_addr(&hdmi.wp),
		.ops = &hdmi_audio_ops,
	};

	hdmi.audio_pdev = platform_device_register_data(
		dev, "omap-hdmi-audio", PLATFORM_DEVID_AUTO,
		&pdata, sizeof(pdata));

	return PTR_ERR_OR_ZERO(hdmi.audio_pdev);
}