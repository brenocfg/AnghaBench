#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct ufx_data {scalar_t__ fb_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_4__ {int smem_len; } ;
struct fb_info {TYPE_2__* fbdefio; TYPE_3__ var; TYPE_1__ fix; scalar_t__ screen_base; struct ufx_data* par; } ;
struct TYPE_5__ {int /*<<< orphan*/  delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFX_DEFIO_WRITE_DELAY ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufx_handle_damage (struct ufx_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ufx_set_vid_mode (struct ufx_data*,TYPE_3__*) ; 

__attribute__((used)) static int ufx_ops_set_par(struct fb_info *info)
{
	struct ufx_data *dev = info->par;
	int result;
	u16 *pix_framebuffer;
	int i;

	pr_debug("set_par mode %dx%d", info->var.xres, info->var.yres);
	result = ufx_set_vid_mode(dev, &info->var);

	if ((result == 0) && (dev->fb_count == 0)) {
		/* paint greenscreen */
		pix_framebuffer = (u16 *) info->screen_base;
		for (i = 0; i < info->fix.smem_len / 2; i++)
			pix_framebuffer[i] = 0x37e6;

		ufx_handle_damage(dev, 0, 0, info->var.xres, info->var.yres);
	}

	/* re-enable defio if previously disabled by damage tracking */
	if (info->fbdefio)
		info->fbdefio->delay = UFX_DEFIO_WRITE_DELAY;

	return result;
}