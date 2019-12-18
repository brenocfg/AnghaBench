#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct spi_device {int bits_per_word; struct device dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct ld9040 {TYPE_2__ panel; int /*<<< orphan*/  reset_gpio; TYPE_1__* supplies; scalar_t__ brightness; struct device* dev; } ;
struct TYPE_6__ {char* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ld9040* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int drm_panel_add (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_2__*) ; 
 int /*<<< orphan*/  ld9040_drm_funcs ; 
 TYPE_1__* ld9040_gammas ; 
 int ld9040_parse_dt (struct ld9040*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ld9040*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int ld9040_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct ld9040 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(struct ld9040), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	spi_set_drvdata(spi, ctx);

	ctx->dev = dev;
	ctx->brightness = ARRAY_SIZE(ld9040_gammas) - 1;

	ret = ld9040_parse_dt(ctx);
	if (ret < 0)
		return ret;

	ctx->supplies[0].supply = "vdd3";
	ctx->supplies[1].supply = "vci";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0)
		return ret;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio)) {
		dev_err(dev, "cannot get reset-gpios %ld\n",
			PTR_ERR(ctx->reset_gpio));
		return PTR_ERR(ctx->reset_gpio);
	}

	spi->bits_per_word = 9;
	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(dev, "spi setup failed.\n");
		return ret;
	}

	drm_panel_init(&ctx->panel);
	ctx->panel.dev = dev;
	ctx->panel.funcs = &ld9040_drm_funcs;

	return drm_panel_add(&ctx->panel);
}