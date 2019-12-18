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
struct omapfb_info {int /*<<< orphan*/  id; struct omapfb2_mem_region* region; struct omapfb2_device* fbdev; } ;
struct omapfb2_mem_region {unsigned long size; unsigned long paddr; int type; } ;
struct omapfb2_device {int dummy; } ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {struct fb_var_screeninfo var; } ;
typedef  int /*<<< orphan*/  new_var ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EINVAL ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int OMAPFB_MEMTYPE_SDRAM ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int check_fb_var (struct fb_info*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  clear_fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  memcpy (struct fb_var_screeninfo*,struct fb_var_screeninfo*,int) ; 
 int omapfb_alloc_fbmem (struct fb_info*,unsigned long,unsigned long) ; 
 int omapfb_apply_changes (struct fb_info*,int) ; 
 int /*<<< orphan*/  omapfb_clear_fb (struct fb_info*) ; 
 int omapfb_fb_init (struct omapfb2_device*,struct fb_info*) ; 
 int /*<<< orphan*/  omapfb_free_fbmem (struct fb_info*) ; 
 int /*<<< orphan*/  set_fb_fix (struct fb_info*) ; 
 int setup_vrfb_rotation (struct fb_info*) ; 

int omapfb_realloc_fbmem(struct fb_info *fbi, unsigned long size, int type)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct omapfb2_device *fbdev = ofbi->fbdev;
	struct omapfb2_mem_region *rg = ofbi->region;
	unsigned long old_size = rg->size;
	unsigned long old_paddr = rg->paddr;
	int old_type = rg->type;
	int r;

	if (type != OMAPFB_MEMTYPE_SDRAM)
		return -EINVAL;

	size = PAGE_ALIGN(size);

	if (old_size == size && old_type == type)
		return 0;

	omapfb_free_fbmem(fbi);

	if (size == 0) {
		clear_fb_info(fbi);
		return 0;
	}

	r = omapfb_alloc_fbmem(fbi, size, 0);

	if (r) {
		if (old_size)
			omapfb_alloc_fbmem(fbi, old_size, old_paddr);

		if (rg->size == 0)
			clear_fb_info(fbi);

		return r;
	}

	if (old_size == size)
		return 0;

	if (old_size == 0) {
		DBG("initializing fb %d\n", ofbi->id);
		r = omapfb_fb_init(fbdev, fbi);
		if (r) {
			DBG("omapfb_fb_init failed\n");
			goto err;
		}
		r = omapfb_apply_changes(fbi, 1);
		if (r) {
			DBG("omapfb_apply_changes failed\n");
			goto err;
		}
	} else {
		struct fb_var_screeninfo new_var;
		memcpy(&new_var, &fbi->var, sizeof(new_var));
		r = check_fb_var(fbi, &new_var);
		if (r)
			goto err;
		memcpy(&fbi->var, &new_var, sizeof(fbi->var));
		set_fb_fix(fbi);
		r = setup_vrfb_rotation(fbi);
		if (r)
			goto err;
	}

	omapfb_clear_fb(fbi);

	return 0;
err:
	omapfb_free_fbmem(fbi);
	clear_fb_info(fbi);
	return r;
}