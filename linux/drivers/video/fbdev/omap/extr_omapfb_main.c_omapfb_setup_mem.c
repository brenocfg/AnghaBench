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
typedef  scalar_t__ u8 ;
struct TYPE_6__ {scalar_t__ enabled; } ;
struct omapfb_plane_struct {size_t idx; TYPE_2__ info; struct omapfb_device* fbdev; } ;
struct omapfb_mem_region {size_t size; scalar_t__ type; unsigned long paddr; } ;
struct omapfb_mem_info {scalar_t__ type; int /*<<< orphan*/  size; } ;
struct fb_var_screeninfo {int dummy; } ;
struct TYPE_5__ {struct omapfb_mem_region* region; } ;
struct omapfb_device {TYPE_3__* ctrl; struct fb_var_screeninfo new_var; TYPE_1__ mem_desc; } ;
struct TYPE_8__ {scalar_t__ smem_len; scalar_t__ smem_start; } ;
struct fb_info {int /*<<< orphan*/  mm_lock; TYPE_4__ fix; struct fb_var_screeninfo var; struct omapfb_plane_struct* par; } ;
struct TYPE_7__ {int (* setup_mem ) (size_t,size_t,scalar_t__,unsigned long*) ;int /*<<< orphan*/  (* sync ) () ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ OMAPFB_MEMTYPE_SDRAM ; 
 size_t PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct fb_var_screeninfo*,struct fb_var_screeninfo*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omapfb_rqueue_lock (struct omapfb_device*) ; 
 int /*<<< orphan*/  omapfb_rqueue_unlock (struct omapfb_device*) ; 
 int /*<<< orphan*/  set_fb_fix (struct fb_info*,int /*<<< orphan*/ ) ; 
 int set_fb_var (struct fb_info*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int stub2 (size_t,size_t,scalar_t__,unsigned long*) ; 

__attribute__((used)) static int omapfb_setup_mem(struct fb_info *fbi, struct omapfb_mem_info *mi)
{
	struct omapfb_plane_struct *plane = fbi->par;
	struct omapfb_device *fbdev = plane->fbdev;
	struct omapfb_mem_region *rg = &fbdev->mem_desc.region[plane->idx];
	size_t size;
	int r = 0;

	if (fbdev->ctrl->setup_mem == NULL)
		return -ENODEV;
	if (mi->type != OMAPFB_MEMTYPE_SDRAM)
		return -EINVAL;

	size = PAGE_ALIGN(mi->size);
	omapfb_rqueue_lock(fbdev);
	if (plane->info.enabled) {
		r = -EBUSY;
		goto out;
	}
	if (rg->size != size || rg->type != mi->type) {
		struct fb_var_screeninfo *new_var = &fbdev->new_var;
		unsigned long old_size = rg->size;
		u8	      old_type = rg->type;
		unsigned long paddr;

		rg->size = size;
		rg->type = mi->type;
		/*
		 * size == 0 is a special case, for which we
		 * don't check / adjust the screen parameters.
		 * This isn't a problem since the plane can't
		 * be reenabled unless its size is > 0.
		 */
		if (old_size != size && size) {
			if (size) {
				memcpy(new_var, &fbi->var, sizeof(*new_var));
				r = set_fb_var(fbi, new_var);
				if (r < 0)
					goto out;
			}
		}

		if (fbdev->ctrl->sync)
			fbdev->ctrl->sync();
		r = fbdev->ctrl->setup_mem(plane->idx, size, mi->type, &paddr);
		if (r < 0) {
			/* Revert changes. */
			rg->size = old_size;
			rg->type = old_type;
			goto out;
		}
		rg->paddr = paddr;

		if (old_size != size) {
			if (size) {
				memcpy(&fbi->var, new_var, sizeof(fbi->var));
				set_fb_fix(fbi, 0);
			} else {
				/*
				 * Set these explicitly to indicate that the
				 * plane memory is dealloce'd, the other
				 * screen parameters in var / fix are invalid.
				 */
				mutex_lock(&fbi->mm_lock);
				fbi->fix.smem_start = 0;
				fbi->fix.smem_len = 0;
				mutex_unlock(&fbi->mm_lock);
			}
		}
	}
out:
	omapfb_rqueue_unlock(fbdev);

	return r;
}