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
typedef  int /*<<< orphan*/  u32 ;
struct zorro_device_id {int dummy; } ;
struct zorro_dev {scalar_t__ id; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; scalar_t__ smem_start; scalar_t__ mmio_start; } ;
struct fb_info {scalar_t__ screen_base; int /*<<< orphan*/  cmap; int /*<<< orphan*/  flags; TYPE_1__ fix; int /*<<< orphan*/ * par; int /*<<< orphan*/ * pseudo_palette; int /*<<< orphan*/  var; int /*<<< orphan*/ * fbops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int FM2FB_MODE_PAL ; 
 scalar_t__ FRAMEMASTER_REG ; 
 int /*<<< orphan*/  FRAMEMASTER_SIZE ; 
 scalar_t__ ZORRO_PROD_BSC_FRAMEMASTER_II ; 
 scalar_t__ fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 TYPE_1__ fb_fix ; 
 int /*<<< orphan*/  fb_info (struct fb_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fb_var_modes ; 
 int /*<<< orphan*/  fm2fb_blank (int /*<<< orphan*/ ,struct fb_info*) ; 
 int fm2fb_mode ; 
 int /*<<< orphan*/  fm2fb_ops ; 
 unsigned char* fm2fb_reg ; 
 struct fb_info* framebuffer_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 scalar_t__ ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 scalar_t__ register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zorro_release_device (struct zorro_dev*) ; 
 int /*<<< orphan*/  zorro_request_device (struct zorro_dev*,char*) ; 
 scalar_t__ zorro_resource_start (struct zorro_dev*) ; 

__attribute__((used)) static int fm2fb_probe(struct zorro_dev *z, const struct zorro_device_id *id)
{
	struct fb_info *info;
	unsigned long *ptr;
	int is_fm;
	int x, y;

	is_fm = z->id == ZORRO_PROD_BSC_FRAMEMASTER_II;

	if (!zorro_request_device(z,"fm2fb"))
		return -ENXIO;

	info = framebuffer_alloc(16 * sizeof(u32), &z->dev);
	if (!info) {
		zorro_release_device(z);
		return -ENOMEM;
	}

	if (fb_alloc_cmap(&info->cmap, 256, 0) < 0) {
		framebuffer_release(info);
		zorro_release_device(z);
		return -ENOMEM;
	}

	/* assigning memory to kernel space */
	fb_fix.smem_start = zorro_resource_start(z);
	info->screen_base = ioremap(fb_fix.smem_start, FRAMEMASTER_SIZE);
	fb_fix.mmio_start = fb_fix.smem_start + FRAMEMASTER_REG;
	fm2fb_reg  = (unsigned char *)(info->screen_base+FRAMEMASTER_REG);

	strcpy(fb_fix.id, is_fm ? "FrameMaster II" : "Rainbow II");

	/* make EBU color bars on display */
	ptr = (unsigned long *)fb_fix.smem_start;
	for (y = 0; y < 576; y++) {
		for (x = 0; x < 96; x++) *ptr++ = 0xffffff;/* white */
		for (x = 0; x < 96; x++) *ptr++ = 0xffff00;/* yellow */
		for (x = 0; x < 96; x++) *ptr++ = 0x00ffff;/* cyan */
		for (x = 0; x < 96; x++) *ptr++ = 0x00ff00;/* green */
		for (x = 0; x < 96; x++) *ptr++ = 0xff00ff;/* magenta */
		for (x = 0; x < 96; x++) *ptr++ = 0xff0000;/* red */
		for (x = 0; x < 96; x++) *ptr++ = 0x0000ff;/* blue */
		for (x = 0; x < 96; x++) *ptr++ = 0x000000;/* black */
	}
	fm2fb_blank(0, info);

	if (fm2fb_mode == -1)
		fm2fb_mode = FM2FB_MODE_PAL;

	info->fbops = &fm2fb_ops;
	info->var = fb_var_modes[fm2fb_mode];
	info->pseudo_palette = info->par;
	info->par = NULL;
	info->fix = fb_fix;
	info->flags = FBINFO_DEFAULT;

	if (register_framebuffer(info) < 0) {
		fb_dealloc_cmap(&info->cmap);
		iounmap(info->screen_base);
		framebuffer_release(info);
		zorro_release_device(z);
		return -EINVAL;
	}
	fb_info(info, "%s frame buffer device\n", fb_fix.id);
	return 0;
}