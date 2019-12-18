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
struct platform_device_info {int size_data; int /*<<< orphan*/  dma_mask; struct hdmi_codec_pdata* data; int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; struct dw_hdmi_i2s_audio_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct hdmi_codec_pdata {int i2s; int max_i2s_channels; struct dw_hdmi_i2s_audio_data* data; int /*<<< orphan*/ * ops; } ;
struct dw_hdmi_i2s_audio_data {int dummy; } ;
typedef  int /*<<< orphan*/  pdevinfo ;
typedef  int /*<<< orphan*/  pdata ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  HDMI_CODEC_DRV_NAME ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct platform_device*) ; 
 int /*<<< orphan*/  dw_hdmi_i2s_ops ; 
 int /*<<< orphan*/  memset (struct platform_device_info*,int /*<<< orphan*/ ,int) ; 
 struct platform_device* platform_device_register_full (struct platform_device_info*) ; 

__attribute__((used)) static int snd_dw_hdmi_probe(struct platform_device *pdev)
{
	struct dw_hdmi_i2s_audio_data *audio = pdev->dev.platform_data;
	struct platform_device_info pdevinfo;
	struct hdmi_codec_pdata pdata;
	struct platform_device *platform;

	pdata.ops		= &dw_hdmi_i2s_ops;
	pdata.i2s		= 1;
	pdata.max_i2s_channels	= 8;
	pdata.data		= audio;

	memset(&pdevinfo, 0, sizeof(pdevinfo));
	pdevinfo.parent		= pdev->dev.parent;
	pdevinfo.id		= PLATFORM_DEVID_AUTO;
	pdevinfo.name		= HDMI_CODEC_DRV_NAME;
	pdevinfo.data		= &pdata;
	pdevinfo.size_data	= sizeof(pdata);
	pdevinfo.dma_mask	= DMA_BIT_MASK(32);

	platform = platform_device_register_full(&pdevinfo);
	if (IS_ERR(platform))
		return PTR_ERR(platform);

	dev_set_drvdata(&pdev->dev, platform);

	return 0;
}