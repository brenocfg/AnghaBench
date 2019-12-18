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
struct imxfb_info {int pwmr; } ;

/* Variables and functions */
 struct imxfb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imxfb_lcd_get_contrast(struct lcd_device *lcddev)
{
	struct imxfb_info *fbi = dev_get_drvdata(&lcddev->dev);

	return fbi->pwmr & 0xff;
}