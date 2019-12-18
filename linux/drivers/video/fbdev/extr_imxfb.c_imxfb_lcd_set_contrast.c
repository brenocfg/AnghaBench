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
struct lcd_device {int /*<<< orphan*/  dev; } ;
struct imxfb_info {int pwmr; scalar_t__ regs; scalar_t__ enabled; } ;

/* Variables and functions */
 scalar_t__ LCDC_PWMR ; 
 struct imxfb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int imxfb_lcd_set_contrast(struct lcd_device *lcddev, int contrast)
{
	struct imxfb_info *fbi = dev_get_drvdata(&lcddev->dev);

	if (fbi->pwmr && fbi->enabled) {
		if (contrast > 255)
			contrast = 255;
		else if (contrast < 0)
			contrast = 0;

		fbi->pwmr &= ~0xff;
		fbi->pwmr |= contrast;

		writel(fbi->pwmr, fbi->regs + LCDC_PWMR);
	}

	return 0;
}