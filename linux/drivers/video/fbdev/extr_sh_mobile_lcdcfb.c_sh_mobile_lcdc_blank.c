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
struct sh_mobile_lcdc_priv {int dummy; } ;
struct sh_mobile_lcdc_chan {int blank_status; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; struct sh_mobile_lcdc_priv* lcdc; } ;
struct fb_info {int /*<<< orphan*/  fbdefio; struct sh_mobile_lcdc_chan* par; } ;
struct fb_fillrect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int FB_BLANK_NORMAL ; 
 int FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  sh_mobile_lcdc_clk_off (struct sh_mobile_lcdc_priv*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_clk_on (struct sh_mobile_lcdc_priv*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_fillrect (struct fb_info*,struct fb_fillrect*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_wait_for_vsync (struct sh_mobile_lcdc_chan*) ; 

__attribute__((used)) static int sh_mobile_lcdc_blank(int blank, struct fb_info *info)
{
	struct sh_mobile_lcdc_chan *ch = info->par;
	struct sh_mobile_lcdc_priv *p = ch->lcdc;

	/* blank the screen? */
	if (blank > FB_BLANK_UNBLANK && ch->blank_status == FB_BLANK_UNBLANK) {
		struct fb_fillrect rect = {
			.width = ch->xres,
			.height = ch->yres,
		};
		sh_mobile_lcdc_fillrect(info, &rect);
	}
	/* turn clocks on? */
	if (blank <= FB_BLANK_NORMAL && ch->blank_status > FB_BLANK_NORMAL) {
		sh_mobile_lcdc_clk_on(p);
	}
	/* turn clocks off? */
	if (blank > FB_BLANK_NORMAL && ch->blank_status <= FB_BLANK_NORMAL) {
		/* make sure the screen is updated with the black fill before
		 * switching the clocks off. one vsync is not enough since
		 * blanking may occur in the middle of a refresh. deferred io
		 * mode will reenable the clocks and update the screen in time,
		 * so it does not need this. */
		if (!info->fbdefio) {
			sh_mobile_lcdc_wait_for_vsync(ch);
			sh_mobile_lcdc_wait_for_vsync(ch);
		}
		sh_mobile_lcdc_clk_off(p);
	}

	ch->blank_status = blank;
	return 0;
}