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
struct fb_info {struct clps711x_fb_info* par; } ;
struct clps711x_fb_info {int dummy; } ;

/* Variables and functions */
 struct clps711x_fb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clps711x_lcd_check_fb(struct lcd_device *lcddev, struct fb_info *fi)
{
	struct clps711x_fb_info *cfb = dev_get_drvdata(&lcddev->dev);

	return (!fi || fi->par == cfb) ? 1 : 0;
}