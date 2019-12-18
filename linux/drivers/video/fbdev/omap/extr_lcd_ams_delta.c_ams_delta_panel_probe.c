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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_contrast; } ;
struct lcd_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_DELTA_DEFAULT_CONTRAST ; 
 int /*<<< orphan*/  AMS_DELTA_MAX_CONTRAST ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 int PTR_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  ams_delta_lcd_ops ; 
 int /*<<< orphan*/  ams_delta_lcd_set_contrast (struct lcd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ams_delta_lcd_set_power (struct lcd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ams_delta_panel ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct lcd_device* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct lcd_device* gpiod_ndisp ; 
 struct lcd_device* gpiod_vblen ; 
 struct lcd_device* lcd_device_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omapfb_register_panel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lcd_device*) ; 

__attribute__((used)) static int ams_delta_panel_probe(struct platform_device *pdev)
{
	struct lcd_device *lcd_device = NULL;
	int ret;

	gpiod_vblen = devm_gpiod_get(&pdev->dev, "vblen", GPIOD_OUT_LOW);
	if (IS_ERR(gpiod_vblen)) {
		ret = PTR_ERR(gpiod_vblen);
		dev_err(&pdev->dev, "VBLEN GPIO request failed (%d)\n", ret);
		return ret;
	}

	gpiod_ndisp = devm_gpiod_get(&pdev->dev, "ndisp", GPIOD_OUT_LOW);
	if (IS_ERR(gpiod_ndisp)) {
		ret = PTR_ERR(gpiod_ndisp);
		dev_err(&pdev->dev, "NDISP GPIO request failed (%d)\n", ret);
		return ret;
	}

#ifdef CONFIG_LCD_CLASS_DEVICE
	lcd_device = lcd_device_register("omapfb", &pdev->dev, NULL,
						&ams_delta_lcd_ops);

	if (IS_ERR(lcd_device)) {
		ret = PTR_ERR(lcd_device);
		dev_err(&pdev->dev, "failed to register device\n");
		return ret;
	}

	platform_set_drvdata(pdev, lcd_device);
	lcd_device->props.max_contrast = AMS_DELTA_MAX_CONTRAST;
#endif

	ams_delta_lcd_set_contrast(lcd_device, AMS_DELTA_DEFAULT_CONTRAST);
	ams_delta_lcd_set_power(lcd_device, FB_BLANK_UNBLANK);

	omapfb_register_panel(&ams_delta_panel);
	return 0;
}