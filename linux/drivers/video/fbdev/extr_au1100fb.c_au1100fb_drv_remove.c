#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cmap; } ;
struct au1100fb_device {scalar_t__ lcdclk; TYPE_2__ info; TYPE_1__* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  lcd_control; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  LCD_CONTROL_GO ; 
 int /*<<< orphan*/  VESA_POWERDOWN ; 
 int /*<<< orphan*/  au1100fb_fb_blank (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 struct au1100fb_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_2__*) ; 

int au1100fb_drv_remove(struct platform_device *dev)
{
	struct au1100fb_device *fbdev = NULL;

	if (!dev)
		return -ENODEV;

	fbdev = platform_get_drvdata(dev);

#if !defined(CONFIG_FRAMEBUFFER_CONSOLE) && defined(CONFIG_LOGO)
	au1100fb_fb_blank(VESA_POWERDOWN, &fbdev->info);
#endif
	fbdev->regs->lcd_control &= ~LCD_CONTROL_GO;

	/* Clean up all probe data */
	unregister_framebuffer(&fbdev->info);

	fb_dealloc_cmap(&fbdev->info.cmap);

	if (fbdev->lcdclk) {
		clk_disable_unprepare(fbdev->lcdclk);
		clk_put(fbdev->lcdclk);
	}

	return 0;
}