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
struct device {int dummy; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  mode; struct device dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct s6e63m0 {int enabled; int prepared; TYPE_1__ panel; int /*<<< orphan*/  reset_gpio; TYPE_3__* supplies; struct device* dev; } ;
struct TYPE_6__ {char* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MODE_3 ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct s6e63m0* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int s6e63m0_backlight_register (struct s6e63m0*) ; 
 int /*<<< orphan*/  s6e63m0_drm_funcs ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct s6e63m0*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int s6e63m0_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct s6e63m0 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(struct s6e63m0), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	spi_set_drvdata(spi, ctx);

	ctx->dev = dev;
	ctx->enabled = false;
	ctx->prepared = false;

	ctx->supplies[0].supply = "vdd3";
	ctx->supplies[1].supply = "vci";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0) {
		DRM_DEV_ERROR(dev, "failed to get regulators: %d\n", ret);
		return ret;
	}

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio)) {
		DRM_DEV_ERROR(dev, "cannot get reset-gpios %ld\n",
			      PTR_ERR(ctx->reset_gpio));
		return PTR_ERR(ctx->reset_gpio);
	}

	spi->bits_per_word = 9;
	spi->mode = SPI_MODE_3;
	ret = spi_setup(spi);
	if (ret < 0) {
		DRM_DEV_ERROR(dev, "spi setup failed.\n");
		return ret;
	}

	drm_panel_init(&ctx->panel);
	ctx->panel.dev = dev;
	ctx->panel.funcs = &s6e63m0_drm_funcs;

	ret = s6e63m0_backlight_register(ctx);
	if (ret < 0)
		return ret;

	return drm_panel_add(&ctx->panel);
}