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
struct omap_hdmi_audio_pdata {int version; int /*<<< orphan*/ * ops; int /*<<< orphan*/  audio_dma_addr; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  pdata ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__ wp; int /*<<< orphan*/  wp_idlemode; int /*<<< orphan*/  audio_pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_WP_SYSCONFIG ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__ hdmi ; 
 int /*<<< orphan*/  hdmi_audio_ops ; 
 int /*<<< orphan*/  hdmi_runtime_get () ; 
 int /*<<< orphan*/  hdmi_runtime_put () ; 
 int /*<<< orphan*/  hdmi_wp_get_audio_dma_addr (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_device_register_data (struct device*,char*,int /*<<< orphan*/ ,struct omap_hdmi_audio_pdata*,int) ; 

__attribute__((used)) static int hdmi_audio_register(struct device *dev)
{
	struct omap_hdmi_audio_pdata pdata = {
		.dev = dev,
		.version = 5,
		.audio_dma_addr = hdmi_wp_get_audio_dma_addr(&hdmi.wp),
		.ops = &hdmi_audio_ops,
	};

	hdmi.audio_pdev = platform_device_register_data(
		dev, "omap-hdmi-audio", PLATFORM_DEVID_AUTO,
		&pdata, sizeof(pdata));

	if (IS_ERR(hdmi.audio_pdev))
		return PTR_ERR(hdmi.audio_pdev);

	hdmi_runtime_get();
	hdmi.wp_idlemode =
		REG_GET(hdmi.wp.base, HDMI_WP_SYSCONFIG, 3, 2);
	hdmi_runtime_put();

	return 0;
}