#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct truly_nt35597 {TYPE_1__ panel; void* mode_gpio; void* reset_gpio; TYPE_3__* supplies; struct nt35597_config* config; struct device* dev; } ;
struct nt35597_config {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  gpiod_set_value (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regulator_names ; 
 int /*<<< orphan*/  truly_nt35597_drm_funcs ; 

__attribute__((used)) static int truly_nt35597_panel_add(struct truly_nt35597 *ctx)
{
	struct device *dev = ctx->dev;
	int ret, i;
	const struct nt35597_config *config;

	config = ctx->config;
	for (i = 0; i < ARRAY_SIZE(ctx->supplies); i++)
		ctx->supplies[i].supply = regulator_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0)
		return ret;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->reset_gpio)) {
		DRM_DEV_ERROR(dev, "cannot get reset gpio %ld\n",
			PTR_ERR(ctx->reset_gpio));
		return PTR_ERR(ctx->reset_gpio);
	}

	ctx->mode_gpio = devm_gpiod_get(dev, "mode", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->mode_gpio)) {
		DRM_DEV_ERROR(dev, "cannot get mode gpio %ld\n",
			PTR_ERR(ctx->mode_gpio));
		return PTR_ERR(ctx->mode_gpio);
	}

	/* dual port */
	gpiod_set_value(ctx->mode_gpio, 0);

	drm_panel_init(&ctx->panel);
	ctx->panel.dev = dev;
	ctx->panel.funcs = &truly_nt35597_drm_funcs;
	drm_panel_add(&ctx->panel);

	return 0;
}