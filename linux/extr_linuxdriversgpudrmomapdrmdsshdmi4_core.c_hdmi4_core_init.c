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
struct soc_device_attribute {struct hdmi4_features* data; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hdmi_core_data {int /*<<< orphan*/  base; int /*<<< orphan*/  audio_use_mclk; int /*<<< orphan*/  cts_swmode; } ;
struct hdmi4_features {int /*<<< orphan*/  audio_use_mclk; int /*<<< orphan*/  cts_swmode; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  hdmi4_soc_devices ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 struct soc_device_attribute* soc_device_match (int /*<<< orphan*/ ) ; 

int hdmi4_core_init(struct platform_device *pdev, struct hdmi_core_data *core)
{
	const struct hdmi4_features *features;
	struct resource *res;
	const struct soc_device_attribute *soc;

	soc = soc_device_match(hdmi4_soc_devices);
	if (!soc)
		return -ENODEV;

	features = soc->data;
	core->cts_swmode = features->cts_swmode;
	core->audio_use_mclk = features->audio_use_mclk;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "core");
	core->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(core->base))
		return PTR_ERR(core->base);

	return 0;
}