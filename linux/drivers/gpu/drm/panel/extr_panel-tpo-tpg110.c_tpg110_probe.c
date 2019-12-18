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
struct TYPE_3__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct tpg110 {TYPE_1__ panel; struct spi_device* spi; int /*<<< orphan*/  grestb; int /*<<< orphan*/  backlight; int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct device* dev; } ;
struct device {struct device_node* of_node; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  mode; struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_3WIRE_HIZ ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct tpg110* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_of_find_backlight (struct device*) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct tpg110*) ; 
 int spi_setup (struct spi_device*) ; 
 int /*<<< orphan*/  tpg110_drm_funcs ; 
 int tpg110_startup (struct tpg110*) ; 

__attribute__((used)) static int tpg110_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct device_node *np = dev->of_node;
	struct tpg110 *tpg;
	int ret;

	tpg = devm_kzalloc(dev, sizeof(*tpg), GFP_KERNEL);
	if (!tpg)
		return -ENOMEM;
	tpg->dev = dev;

	/* We get the physical display dimensions from the DT */
	ret = of_property_read_u32(np, "width-mm", &tpg->width);
	if (ret)
		DRM_DEV_ERROR(dev, "no panel width specified\n");
	ret = of_property_read_u32(np, "height-mm", &tpg->height);
	if (ret)
		DRM_DEV_ERROR(dev, "no panel height specified\n");

	/* Look for some optional backlight */
	tpg->backlight = devm_of_find_backlight(dev);
	if (IS_ERR(tpg->backlight))
		return PTR_ERR(tpg->backlight);

	/* This asserts the GRESTB signal, putting the display into reset */
	tpg->grestb = devm_gpiod_get(dev, "grestb", GPIOD_OUT_HIGH);
	if (IS_ERR(tpg->grestb)) {
		DRM_DEV_ERROR(dev, "no GRESTB GPIO\n");
		return -ENODEV;
	}

	spi->bits_per_word = 8;
	spi->mode |= SPI_3WIRE_HIZ;
	ret = spi_setup(spi);
	if (ret < 0) {
		DRM_DEV_ERROR(dev, "spi setup failed.\n");
		return ret;
	}
	tpg->spi = spi;

	ret = tpg110_startup(tpg);
	if (ret)
		return ret;

	drm_panel_init(&tpg->panel);
	tpg->panel.dev = dev;
	tpg->panel.funcs = &tpg110_drm_funcs;
	spi_set_drvdata(spi, tpg);

	return drm_panel_add(&tpg->panel);
}