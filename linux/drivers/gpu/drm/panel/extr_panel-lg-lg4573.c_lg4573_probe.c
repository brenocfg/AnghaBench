#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/ * dev; } ;
struct lg4573 {TYPE_1__ panel; struct spi_device* spi; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct lg4573* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  lg4573_drm_funcs ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct lg4573*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int lg4573_probe(struct spi_device *spi)
{
	struct lg4573 *ctx;
	int ret;

	ctx = devm_kzalloc(&spi->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->spi = spi;

	spi_set_drvdata(spi, ctx);
	spi->bits_per_word = 8;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "SPI setup failed: %d\n", ret);
		return ret;
	}

	drm_panel_init(&ctx->panel);
	ctx->panel.dev = &spi->dev;
	ctx->panel.funcs = &lg4573_drm_funcs;

	return drm_panel_add(&ctx->panel);
}