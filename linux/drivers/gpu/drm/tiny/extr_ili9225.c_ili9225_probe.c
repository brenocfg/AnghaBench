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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct spi_device {struct device dev; } ;
struct drm_device {int dummy; } ;
struct mipi_dbi {int /*<<< orphan*/  command; struct gpio_desc* reset; } ;
struct mipi_dbi_dev {struct drm_device drm; struct mipi_dbi dbi; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 int devm_drm_dev_init (struct device*,struct drm_device*,int /*<<< orphan*/ *) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int /*<<< orphan*/  ili9225_dbi_command ; 
 int /*<<< orphan*/  ili9225_driver ; 
 int /*<<< orphan*/  ili9225_mode ; 
 int /*<<< orphan*/  ili9225_pipe_funcs ; 
 int /*<<< orphan*/  kfree (struct mipi_dbi_dev*) ; 
 struct mipi_dbi_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mipi_dbi_dev_init (struct mipi_dbi_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mipi_dbi_spi_init (struct spi_device*,struct mipi_dbi*,struct gpio_desc*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct drm_device*) ; 

__attribute__((used)) static int ili9225_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct mipi_dbi_dev *dbidev;
	struct drm_device *drm;
	struct mipi_dbi *dbi;
	struct gpio_desc *rs;
	u32 rotation = 0;
	int ret;

	dbidev = kzalloc(sizeof(*dbidev), GFP_KERNEL);
	if (!dbidev)
		return -ENOMEM;

	dbi = &dbidev->dbi;
	drm = &dbidev->drm;
	ret = devm_drm_dev_init(dev, drm, &ili9225_driver);
	if (ret) {
		kfree(dbidev);
		return ret;
	}

	drm_mode_config_init(drm);

	dbi->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(dbi->reset)) {
		DRM_DEV_ERROR(dev, "Failed to get gpio 'reset'\n");
		return PTR_ERR(dbi->reset);
	}

	rs = devm_gpiod_get(dev, "rs", GPIOD_OUT_LOW);
	if (IS_ERR(rs)) {
		DRM_DEV_ERROR(dev, "Failed to get gpio 'rs'\n");
		return PTR_ERR(rs);
	}

	device_property_read_u32(dev, "rotation", &rotation);

	ret = mipi_dbi_spi_init(spi, dbi, rs);
	if (ret)
		return ret;

	/* override the command function set in  mipi_dbi_spi_init() */
	dbi->command = ili9225_dbi_command;

	ret = mipi_dbi_dev_init(dbidev, &ili9225_pipe_funcs, &ili9225_mode, rotation);
	if (ret)
		return ret;

	drm_mode_config_reset(drm);

	ret = drm_dev_register(drm, 0);
	if (ret)
		return ret;

	spi_set_drvdata(spi, drm);

	drm_fbdev_generic_setup(drm, 0);

	return 0;
}