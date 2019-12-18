#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; } ;
struct i810fb_par {int dev_flags; int ddc_num; int /*<<< orphan*/  i810fb_ops; TYPE_1__ aperture; int /*<<< orphan*/  open_lock; } ;
struct TYPE_4__ {int xres; int yres; int yres_virtual; int bits_per_pixel; int nonstd; int accel_flags; } ;
struct fb_info {TYPE_2__ var; } ;

/* Variables and functions */
 int ALWAYS_SYNC ; 
 int HAS_ACCELERATION ; 
 scalar_t__ accel ; 
 int bpp ; 
 scalar_t__ dcolor ; 
 scalar_t__ ddc3 ; 
 int /*<<< orphan*/  i810_init_monspecs (struct fb_info*) ; 
 int /*<<< orphan*/  i810fb_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ sync ; 
 int v_offset_default ; 
 int voffset ; 
 int vram ; 
 int vyres ; 
 int xres ; 
 int yres ; 

__attribute__((used)) static void i810_init_defaults(struct i810fb_par *par, struct fb_info *info)
{
	mutex_init(&par->open_lock);

	if (voffset) 
		v_offset_default = voffset;
	else if (par->aperture.size > 32 * 1024 * 1024)
		v_offset_default = 16;
	else
		v_offset_default = 8;

	if (!vram) 
		vram = 1;

	if (accel) 
		par->dev_flags |= HAS_ACCELERATION;

	if (sync) 
		par->dev_flags |= ALWAYS_SYNC;

	par->ddc_num = (ddc3 ? 3 : 2);

	if (bpp < 8)
		bpp = 8;
	
	par->i810fb_ops = i810fb_ops;

	if (xres)
		info->var.xres = xres;
	else
		info->var.xres = 640;

	if (yres)
		info->var.yres = yres;
	else
		info->var.yres = 480;

	if (!vyres) 
		vyres = (vram << 20)/(info->var.xres*bpp >> 3);

	info->var.yres_virtual = vyres;
	info->var.bits_per_pixel = bpp;

	if (dcolor)
		info->var.nonstd = 1;

	if (par->dev_flags & HAS_ACCELERATION) 
		info->var.accel_flags = 1;

	i810_init_monspecs(info);
}