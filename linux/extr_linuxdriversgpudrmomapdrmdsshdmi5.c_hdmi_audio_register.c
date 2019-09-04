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
struct omap_hdmi_audio_pdata {int version; int /*<<< orphan*/ * ops; int /*<<< orphan*/  audio_dma_addr; int /*<<< orphan*/ * dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct omap_hdmi {TYPE_2__ wp; int /*<<< orphan*/  wp_idlemode; int /*<<< orphan*/  audio_pdev; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  pdata ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_WP_SYSCONFIG ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hdmi_audio_ops ; 
 int /*<<< orphan*/  hdmi_runtime_get (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_runtime_put (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_wp_get_audio_dma_addr (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_device_register_data (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct omap_hdmi_audio_pdata*,int) ; 

__attribute__((used)) static int hdmi_audio_register(struct omap_hdmi *hdmi)
{
	struct omap_hdmi_audio_pdata pdata = {
		.dev = &hdmi->pdev->dev,
		.version = 5,
		.audio_dma_addr = hdmi_wp_get_audio_dma_addr(&hdmi->wp),
		.ops = &hdmi_audio_ops,
	};

	hdmi->audio_pdev = platform_device_register_data(
		&hdmi->pdev->dev, "omap-hdmi-audio", PLATFORM_DEVID_AUTO,
		&pdata, sizeof(pdata));

	if (IS_ERR(hdmi->audio_pdev))
		return PTR_ERR(hdmi->audio_pdev);

	hdmi_runtime_get(hdmi);
	hdmi->wp_idlemode =
		REG_GET(hdmi->wp.base, HDMI_WP_SYSCONFIG, 3, 2);
	hdmi_runtime_put(hdmi);

	return 0;
}