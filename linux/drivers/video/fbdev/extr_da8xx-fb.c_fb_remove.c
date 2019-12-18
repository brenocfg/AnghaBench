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
struct fb_info {int /*<<< orphan*/  cmap; struct da8xx_fb_par* par; } ;
struct da8xx_fb_par {scalar_t__ lcd_supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA8XX_FRAME_WAIT ; 
 int /*<<< orphan*/  LCD_DMA_CTRL_REG ; 
 int /*<<< orphan*/  LCD_RASTER_CTRL_REG ; 
 struct fb_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  lcd_da8xx_cpufreq_deregister (struct da8xx_fb_par*) ; 
 int /*<<< orphan*/  lcd_disable_raster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int fb_remove(struct platform_device *dev)
{
	struct fb_info *info = dev_get_drvdata(&dev->dev);
	struct da8xx_fb_par *par = info->par;
	int ret;

#ifdef CONFIG_CPU_FREQ
	lcd_da8xx_cpufreq_deregister(par);
#endif
	if (par->lcd_supply) {
		ret = regulator_disable(par->lcd_supply);
		if (ret)
			return ret;
	}

	lcd_disable_raster(DA8XX_FRAME_WAIT);
	lcdc_write(0, LCD_RASTER_CTRL_REG);

	/* disable DMA  */
	lcdc_write(0, LCD_DMA_CTRL_REG);

	unregister_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	pm_runtime_put_sync(&dev->dev);
	pm_runtime_disable(&dev->dev);
	framebuffer_release(info);

	return 0;
}