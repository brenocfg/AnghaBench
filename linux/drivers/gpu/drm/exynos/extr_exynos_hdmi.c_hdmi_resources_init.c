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
struct hdmi_context {scalar_t__ irq; int /*<<< orphan*/  reg_hdmi_en; TYPE_1__* regul_bulk; int /*<<< orphan*/  hpd_gpio; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (struct device*,char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_regulator_get_optional (struct device*,char*) ; 
 scalar_t__ gpiod_to_irq (int /*<<< orphan*/ ) ; 
 int hdmi_bridge_init (struct hdmi_context*) ; 
 int hdmi_clk_init (struct hdmi_context*) ; 
 int hdmi_clk_set_parents (struct hdmi_context*,int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * supply ; 

__attribute__((used)) static int hdmi_resources_init(struct hdmi_context *hdata)
{
	struct device *dev = hdata->dev;
	int i, ret;

	DRM_DEV_DEBUG_KMS(dev, "HDMI resource init\n");

	hdata->hpd_gpio = devm_gpiod_get(dev, "hpd", GPIOD_IN);
	if (IS_ERR(hdata->hpd_gpio)) {
		DRM_DEV_ERROR(dev, "cannot get hpd gpio property\n");
		return PTR_ERR(hdata->hpd_gpio);
	}

	hdata->irq = gpiod_to_irq(hdata->hpd_gpio);
	if (hdata->irq < 0) {
		DRM_DEV_ERROR(dev, "failed to get GPIO irq\n");
		return  hdata->irq;
	}

	ret = hdmi_clk_init(hdata);
	if (ret)
		return ret;

	ret = hdmi_clk_set_parents(hdata, false);
	if (ret)
		return ret;

	for (i = 0; i < ARRAY_SIZE(supply); ++i)
		hdata->regul_bulk[i].supply = supply[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(supply), hdata->regul_bulk);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "failed to get regulators\n");
		return ret;
	}

	hdata->reg_hdmi_en = devm_regulator_get_optional(dev, "hdmi-en");

	if (PTR_ERR(hdata->reg_hdmi_en) != -ENODEV) {
		if (IS_ERR(hdata->reg_hdmi_en))
			return PTR_ERR(hdata->reg_hdmi_en);

		ret = regulator_enable(hdata->reg_hdmi_en);
		if (ret) {
			DRM_DEV_ERROR(dev,
				      "failed to enable hdmi-en regulator\n");
			return ret;
		}
	}

	return hdmi_bridge_init(hdata);
}