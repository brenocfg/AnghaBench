#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int size; } ;
struct intelfb_info {scalar_t__ accel; TYPE_2__ fb; TYPE_3__* info; TYPE_1__* pdev; int /*<<< orphan*/  initial_var; } ;
struct fb_var_screeninfo {int xres; int yres; int bits_per_pixel; int xres_virtual; int yres_virtual; int /*<<< orphan*/  accel_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  modedb_len; int /*<<< orphan*/ * modedb; } ;
struct TYPE_7__ {TYPE_4__ monspecs; struct fb_var_screeninfo var; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*,...) ; 
 int /*<<< orphan*/  EDID_LENGTH ; 
 int /*<<< orphan*/  ERR_MSG (char*) ; 
 int /*<<< orphan*/  FB_ACCELF_TEXT ; 
 scalar_t__ FIXED_MODE (struct intelfb_info*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INF_MSG (char*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ PREFERRED_MODE ; 
 int /*<<< orphan*/  fb_edid_to_monspecs (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int fb_find_mode (struct fb_var_screeninfo*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fb_firmware_edid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct fb_var_screeninfo*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mode ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  var_to_refresh (struct fb_var_screeninfo*) ; 

__attribute__((used)) static int intelfb_init_var(struct intelfb_info *dinfo)
{
	struct fb_var_screeninfo *var;
	int msrc = 0;

	DBG_MSG("intelfb_init_var\n");

	var = &dinfo->info->var;
	if (FIXED_MODE(dinfo)) {
	        memcpy(var, &dinfo->initial_var,
		       sizeof(struct fb_var_screeninfo));
		msrc = 5;
	} else {
		const u8 *edid_s = fb_firmware_edid(&dinfo->pdev->dev);
		u8 *edid_d = NULL;

		if (edid_s) {
			edid_d = kmemdup(edid_s, EDID_LENGTH, GFP_KERNEL);

			if (edid_d) {
				fb_edid_to_monspecs(edid_d,
						    &dinfo->info->monspecs);
				kfree(edid_d);
			}
		}

		if (mode) {
			printk("intelfb: Looking for mode in private "
			       "database\n");
			msrc = fb_find_mode(var, dinfo->info, mode,
					    dinfo->info->monspecs.modedb,
					    dinfo->info->monspecs.modedb_len,
					    NULL, 0);

			if (msrc && msrc > 1) {
				printk("intelfb: No mode in private database, "
				       "intelfb: looking for mode in global "
				       "database ");
				msrc = fb_find_mode(var, dinfo->info, mode,
						    NULL, 0, NULL, 0);

				if (msrc)
					msrc |= 8;
			}

		}

		if (!msrc)
			msrc = fb_find_mode(var, dinfo->info, PREFERRED_MODE,
					    NULL, 0, NULL, 0);
	}

	if (!msrc) {
		ERR_MSG("Cannot find a suitable video mode.\n");
		return 1;
	}

	INF_MSG("Initial video mode is %dx%d-%d@%d.\n", var->xres, var->yres,
		var->bits_per_pixel, var_to_refresh(var));

	DBG_MSG("Initial video mode is from %d.\n", msrc);

#if ALLOCATE_FOR_PANNING
	/* Allow use of half of the video ram for panning */
	var->xres_virtual = var->xres;
	var->yres_virtual =
		dinfo->fb.size / 2 / (var->bits_per_pixel * var->xres);
	if (var->yres_virtual < var->yres)
		var->yres_virtual = var->yres;
#else
	var->yres_virtual = var->yres;
#endif

	if (dinfo->accel)
		var->accel_flags |= FB_ACCELF_TEXT;
	else
		var->accel_flags &= ~FB_ACCELF_TEXT;

	return 0;
}