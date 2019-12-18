#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int (* fb_check_var ) (TYPE_4__*,struct fb_info*) ;int /*<<< orphan*/ * fb_cursor; } ;
struct sm501fb_par {TYPE_5__ ops; struct sm501fb_info* info; } ;
struct sm501fb_info {TYPE_9__* dev; scalar_t__ edid_data; scalar_t__ regs; TYPE_1__* pdata; } ;
struct sm501_platdata_fbsub {int flags; int def_bpp; scalar_t__ def_mode; } ;
struct fb_ops {int dummy; } ;
struct TYPE_14__ {int bits_per_pixel; int /*<<< orphan*/  yres; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  vmode; scalar_t__ accel_flags; int /*<<< orphan*/  activate; scalar_t__ nonstd; } ;
struct TYPE_16__ {int /*<<< orphan*/  modedb_len; int /*<<< orphan*/ * modedb; } ;
struct TYPE_13__ {int xpanstep; int ypanstep; int /*<<< orphan*/  accel; scalar_t__ ywrapstep; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {int flags; TYPE_4__ var; TYPE_5__* fbops; int /*<<< orphan*/  cmap; TYPE_8__ monspecs; int /*<<< orphan*/  modelist; TYPE_3__ fix; struct sm501fb_par* par; } ;
typedef  enum sm501_controller { ____Placeholder_sm501_controller } sm501_controller ;
struct TYPE_17__ {TYPE_2__* parent; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_11__ {scalar_t__ fb_route; struct sm501_platdata_fbsub* fb_pnl; struct sm501_platdata_fbsub* fb_crt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FBINFO_FLAG_DEFAULT ; 
 int FBINFO_FOREIGN_ENDIAN ; 
 int FBINFO_HWACCEL_COPYAREA ; 
 int FBINFO_HWACCEL_FILLRECT ; 
 int FBINFO_HWACCEL_XPAN ; 
 int FBINFO_HWACCEL_YPAN ; 
 int FBINFO_READS_FAST ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
#define  HEAD_CRT 129 
#define  HEAD_PANEL 128 
 int /*<<< orphan*/  NR_PALETTE ; 
 int SM501FB_FLAG_USE_HWCURSOR ; 
 int SM501FB_FLAG_USE_INIT_MODE ; 
 scalar_t__ SM501_DC_CRT_CONTROL ; 
 unsigned long SM501_DC_CRT_CONTROL_ENABLE ; 
 unsigned long SM501_DC_CRT_CONTROL_SEL ; 
 scalar_t__ SM501_DC_PANEL_CONTROL ; 
 unsigned long SM501_DC_PANEL_CONTROL_EN ; 
 scalar_t__ SM501_FB_CRT_PANEL ; 
 int default_bpp ; 
 int /*<<< orphan*/  dev_err (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_9__*,char*,...) ; 
 scalar_t__ fb_alloc_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_edid_to_monspecs (scalar_t__,TYPE_8__*) ; 
 int fb_find_mode (TYPE_4__*,struct fb_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fb_mode ; 
 int /*<<< orphan*/  fb_set_cmap (int /*<<< orphan*/ *,struct fb_info*) ; 
 int /*<<< orphan*/  fb_videomode_to_modelist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_videomode_to_var (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sm501_default_mode ; 
 int /*<<< orphan*/  sm501fb_ops_crt ; 
 int /*<<< orphan*/  sm501fb_ops_pnl ; 
 unsigned long smc501_readl (scalar_t__) ; 
 int /*<<< orphan*/  smc501_writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int stub1 (TYPE_4__*,struct fb_info*) ; 

__attribute__((used)) static int sm501fb_init_fb(struct fb_info *fb, enum sm501_controller head,
			   const char *fbname)
{
	struct sm501_platdata_fbsub *pd;
	struct sm501fb_par *par = fb->par;
	struct sm501fb_info *info = par->info;
	unsigned long ctrl;
	unsigned int enable;
	int ret;

	switch (head) {
	case HEAD_CRT:
		pd = info->pdata->fb_crt;
		ctrl = smc501_readl(info->regs + SM501_DC_CRT_CONTROL);
		enable = (ctrl & SM501_DC_CRT_CONTROL_ENABLE) ? 1 : 0;

		/* ensure we set the correct source register */
		if (info->pdata->fb_route != SM501_FB_CRT_PANEL) {
			ctrl |= SM501_DC_CRT_CONTROL_SEL;
			smc501_writel(ctrl, info->regs + SM501_DC_CRT_CONTROL);
		}

		break;

	case HEAD_PANEL:
		pd = info->pdata->fb_pnl;
		ctrl = smc501_readl(info->regs + SM501_DC_PANEL_CONTROL);
		enable = (ctrl & SM501_DC_PANEL_CONTROL_EN) ? 1 : 0;
		break;

	default:
		pd = NULL;		/* stop compiler warnings */
		ctrl = 0;
		enable = 0;
		BUG();
	}

	dev_info(info->dev, "fb %s %sabled at start\n",
		 fbname, enable ? "en" : "dis");

	/* check to see if our routing allows this */

	if (head == HEAD_CRT && info->pdata->fb_route == SM501_FB_CRT_PANEL) {
		ctrl &= ~SM501_DC_CRT_CONTROL_SEL;
		smc501_writel(ctrl, info->regs + SM501_DC_CRT_CONTROL);
		enable = 0;
	}

	strlcpy(fb->fix.id, fbname, sizeof(fb->fix.id));

	memcpy(&par->ops,
	       (head == HEAD_CRT) ? &sm501fb_ops_crt : &sm501fb_ops_pnl,
	       sizeof(struct fb_ops));

	/* update ops dependent on what we've been passed */

	if ((pd->flags & SM501FB_FLAG_USE_HWCURSOR) == 0)
		par->ops.fb_cursor = NULL;

	fb->fbops = &par->ops;
	fb->flags = FBINFO_FLAG_DEFAULT | FBINFO_READS_FAST |
		FBINFO_HWACCEL_COPYAREA | FBINFO_HWACCEL_FILLRECT |
		FBINFO_HWACCEL_XPAN | FBINFO_HWACCEL_YPAN;

#if defined(CONFIG_OF)
#ifdef __BIG_ENDIAN
	if (of_get_property(info->dev->parent->of_node, "little-endian", NULL))
		fb->flags |= FBINFO_FOREIGN_ENDIAN;
#else
	if (of_get_property(info->dev->parent->of_node, "big-endian", NULL))
		fb->flags |= FBINFO_FOREIGN_ENDIAN;
#endif
#endif
	/* fixed data */

	fb->fix.type		= FB_TYPE_PACKED_PIXELS;
	fb->fix.type_aux	= 0;
	fb->fix.xpanstep	= 1;
	fb->fix.ypanstep	= 1;
	fb->fix.ywrapstep	= 0;
	fb->fix.accel		= FB_ACCEL_NONE;

	/* screenmode */

	fb->var.nonstd		= 0;
	fb->var.activate	= FB_ACTIVATE_NOW;
	fb->var.accel_flags	= 0;
	fb->var.vmode		= FB_VMODE_NONINTERLACED;
	fb->var.bits_per_pixel  = 16;

	if (info->edid_data) {
			/* Now build modedb from EDID */
			fb_edid_to_monspecs(info->edid_data, &fb->monspecs);
			fb_videomode_to_modelist(fb->monspecs.modedb,
						 fb->monspecs.modedb_len,
						 &fb->modelist);
	}

	if (enable && (pd->flags & SM501FB_FLAG_USE_INIT_MODE) && 0) {
		/* TODO read the mode from the current display */
	} else {
		if (pd->def_mode) {
			dev_info(info->dev, "using supplied mode\n");
			fb_videomode_to_var(&fb->var, pd->def_mode);

			fb->var.bits_per_pixel = pd->def_bpp ? pd->def_bpp : 8;
			fb->var.xres_virtual = fb->var.xres;
			fb->var.yres_virtual = fb->var.yres;
		} else {
			if (info->edid_data) {
				ret = fb_find_mode(&fb->var, fb, fb_mode,
					fb->monspecs.modedb,
					fb->monspecs.modedb_len,
					&sm501_default_mode, default_bpp);
				/* edid_data is no longer needed, free it */
				kfree(info->edid_data);
			} else {
				ret = fb_find_mode(&fb->var, fb,
					   NULL, NULL, 0, NULL, 8);
			}

			switch (ret) {
			case 1:
				dev_info(info->dev, "using mode specified in "
						"@mode\n");
				break;
			case 2:
				dev_info(info->dev, "using mode specified in "
					"@mode with ignored refresh rate\n");
				break;
			case 3:
				dev_info(info->dev, "using mode default "
					"mode\n");
				break;
			case 4:
				dev_info(info->dev, "using mode from list\n");
				break;
			default:
				dev_info(info->dev, "ret = %d\n", ret);
				dev_info(info->dev, "failed to find mode\n");
				return -EINVAL;
			}
		}
	}

	/* initialise and set the palette */
	if (fb_alloc_cmap(&fb->cmap, NR_PALETTE, 0)) {
		dev_err(info->dev, "failed to allocate cmap memory\n");
		return -ENOMEM;
	}
	fb_set_cmap(&fb->cmap, fb);

	ret = (fb->fbops->fb_check_var)(&fb->var, fb);
	if (ret)
		dev_err(info->dev, "check_var() failed on initial setup?\n");

	return 0;
}