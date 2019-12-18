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
struct i810fb_par {int use_count; int /*<<< orphan*/  open_lock; int /*<<< orphan*/  state; } ;
struct fb_info {struct i810fb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  i810_restore_vga_state (struct i810fb_par*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_vga (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i810fb_release(struct fb_info *info, int user)
{
	struct i810fb_par *par = info->par;

	mutex_lock(&par->open_lock);
	if (par->use_count == 0) {
		mutex_unlock(&par->open_lock);
		return -EINVAL;
	}

	if (par->use_count == 1) {
		i810_restore_vga_state(par);
		restore_vga(&par->state);
	}

	par->use_count--;
	mutex_unlock(&par->open_lock);
	
	return 0;
}