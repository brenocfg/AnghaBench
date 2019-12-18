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
struct mfb_info {scalar_t__ index; int count; int /*<<< orphan*/  parent; } ;
struct fb_info {int /*<<< orphan*/  var; struct mfb_info* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release_bootmem ) () ;} ;

/* Variables and functions */
 scalar_t__ PLANE0 ; 
 int /*<<< orphan*/  diu_lock ; 
 TYPE_1__ diu_ops ; 
 int /*<<< orphan*/  fsl_diu_check_var (int /*<<< orphan*/ *,struct fb_info*) ; 
 int /*<<< orphan*/  fsl_diu_enable_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_diu_enable_panel (struct fb_info*) ; 
 int fsl_diu_set_par (struct fb_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int fsl_diu_open(struct fb_info *info, int user)
{
	struct mfb_info *mfbi = info->par;
	int res = 0;

	/* free boot splash memory on first /dev/fb0 open */
	if ((mfbi->index == PLANE0) && diu_ops.release_bootmem)
		diu_ops.release_bootmem();

	spin_lock(&diu_lock);
	mfbi->count++;
	if (mfbi->count == 1) {
		fsl_diu_check_var(&info->var, info);
		res = fsl_diu_set_par(info);
		if (res < 0)
			mfbi->count--;
		else {
			fsl_diu_enable_interrupts(mfbi->parent);
			fsl_diu_enable_panel(info);
		}
	}

	spin_unlock(&diu_lock);
	return res;
}