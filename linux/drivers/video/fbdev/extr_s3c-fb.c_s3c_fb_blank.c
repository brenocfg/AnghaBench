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
typedef  scalar_t__ u32 ;
struct s3c_fb_win {unsigned int index; struct s3c_fb* parent; } ;
struct TYPE_2__ {scalar_t__ wincon; scalar_t__ winmap; } ;
struct s3c_fb {scalar_t__ output_on; int enabled; int /*<<< orphan*/  dev; TYPE_1__ variant; scalar_t__ regs; } ;
struct fb_info {struct s3c_fb_win* par; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 scalar_t__ WINCONx_ENWIN ; 
 scalar_t__ WINxMAP_MAP ; 
 scalar_t__ WINxMAP_MAP_COLOUR (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  s3c_fb_enable (struct s3c_fb*,int) ; 
 int /*<<< orphan*/  shadow_protect_win (struct s3c_fb_win*,int) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int s3c_fb_blank(int blank_mode, struct fb_info *info)
{
	struct s3c_fb_win *win = info->par;
	struct s3c_fb *sfb = win->parent;
	unsigned int index = win->index;
	u32 wincon;
	u32 output_on = sfb->output_on;

	dev_dbg(sfb->dev, "blank mode %d\n", blank_mode);

	pm_runtime_get_sync(sfb->dev);

	wincon = readl(sfb->regs + sfb->variant.wincon + (index * 4));

	switch (blank_mode) {
	case FB_BLANK_POWERDOWN:
		wincon &= ~WINCONx_ENWIN;
		sfb->enabled &= ~(1 << index);
		/* fall through - to FB_BLANK_NORMAL */

	case FB_BLANK_NORMAL:
		/* disable the DMA and display 0x0 (black) */
		shadow_protect_win(win, 1);
		writel(WINxMAP_MAP | WINxMAP_MAP_COLOUR(0x0),
		       sfb->regs + sfb->variant.winmap + (index * 4));
		shadow_protect_win(win, 0);
		break;

	case FB_BLANK_UNBLANK:
		shadow_protect_win(win, 1);
		writel(0x0, sfb->regs + sfb->variant.winmap + (index * 4));
		shadow_protect_win(win, 0);
		wincon |= WINCONx_ENWIN;
		sfb->enabled |= (1 << index);
		break;

	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	default:
		pm_runtime_put_sync(sfb->dev);
		return 1;
	}

	shadow_protect_win(win, 1);
	writel(wincon, sfb->regs + sfb->variant.wincon + (index * 4));

	/* Check the enabled state to see if we need to be running the
	 * main LCD interface, as if there are no active windows then
	 * it is highly likely that we also do not need to output
	 * anything.
	 */
	s3c_fb_enable(sfb, sfb->enabled ? 1 : 0);
	shadow_protect_win(win, 0);

	pm_runtime_put_sync(sfb->dev);

	return output_on == sfb->output_on;
}