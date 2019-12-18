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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  LCD_DEF_CONTRAST ; 
 int PTR_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  S1D_DEVICENAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct lcd_device* devm_lcd_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jornada_lcd_props ; 
 int /*<<< orphan*/  jornada_lcd_set_contrast (struct lcd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jornada_lcd_set_power (struct lcd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lcd_device*) ; 

__attribute__((used)) static int jornada_lcd_probe(struct platform_device *pdev)
{
	struct lcd_device *lcd_device;
	int ret;

	lcd_device = devm_lcd_device_register(&pdev->dev, S1D_DEVICENAME,
					&pdev->dev, NULL, &jornada_lcd_props);

	if (IS_ERR(lcd_device)) {
		ret = PTR_ERR(lcd_device);
		dev_err(&pdev->dev, "failed to register device\n");
		return ret;
	}

	platform_set_drvdata(pdev, lcd_device);

	/* lets set our default values */
	jornada_lcd_set_contrast(lcd_device, LCD_DEF_CONTRAST);
	jornada_lcd_set_power(lcd_device, FB_BLANK_UNBLANK);
	/* give it some time to startup */
	msleep(100);

	return 0;
}