#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct device* dev; int /*<<< orphan*/ * funcs; } ;
struct jdi_panel {TYPE_1__ base; TYPE_2__* dsi; void* backlight; void* dcdc_en_gpio; void* reset_gpio; void* enable_gpio; TYPE_4__* supplies; int /*<<< orphan*/ * mode; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  supply; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  default_mode ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,unsigned int,TYPE_4__*) ; 
 int drm_panel_add (TYPE_1__*) ; 
 void* drm_panel_create_dsi_backlight (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  jdi_panel_funcs ; 
 int /*<<< orphan*/ * regulator_names ; 

__attribute__((used)) static int jdi_panel_add(struct jdi_panel *jdi)
{
	struct device *dev = &jdi->dsi->dev;
	int ret;
	unsigned int i;

	jdi->mode = &default_mode;

	for (i = 0; i < ARRAY_SIZE(jdi->supplies); i++)
		jdi->supplies[i].supply = regulator_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(jdi->supplies),
				      jdi->supplies);
	if (ret < 0) {
		dev_err(dev, "failed to init regulator, ret=%d\n", ret);
		return ret;
	}

	jdi->enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(jdi->enable_gpio)) {
		ret = PTR_ERR(jdi->enable_gpio);
		dev_err(dev, "cannot get enable-gpio %d\n", ret);
		return ret;
	}

	jdi->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(jdi->reset_gpio)) {
		ret = PTR_ERR(jdi->reset_gpio);
		dev_err(dev, "cannot get reset-gpios %d\n", ret);
		return ret;
	}

	jdi->dcdc_en_gpio = devm_gpiod_get(dev, "dcdc-en", GPIOD_OUT_LOW);
	if (IS_ERR(jdi->dcdc_en_gpio)) {
		ret = PTR_ERR(jdi->dcdc_en_gpio);
		dev_err(dev, "cannot get dcdc-en-gpio %d\n", ret);
		return ret;
	}

	jdi->backlight = drm_panel_create_dsi_backlight(jdi->dsi);
	if (IS_ERR(jdi->backlight)) {
		ret = PTR_ERR(jdi->backlight);
		dev_err(dev, "failed to register backlight %d\n", ret);
		return ret;
	}

	drm_panel_init(&jdi->base);
	jdi->base.funcs = &jdi_panel_funcs;
	jdi->base.dev = &jdi->dsi->dev;

	ret = drm_panel_add(&jdi->base);

	return ret;
}