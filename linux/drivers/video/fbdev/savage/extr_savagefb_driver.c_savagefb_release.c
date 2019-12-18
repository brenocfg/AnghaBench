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
struct savagefb_par {int open_count; int /*<<< orphan*/  open_lock; int /*<<< orphan*/  vgastate; int /*<<< orphan*/  initial; } ;
struct fb_info {struct savagefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_vga (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  savage_set_default_par (struct savagefb_par*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int savagefb_release(struct fb_info *info, int user)
{
	struct savagefb_par *par = info->par;

	mutex_lock(&par->open_lock);

	if (par->open_count == 1) {
		savage_set_default_par(par, &par->initial);
		restore_vga(&par->vgastate);
	}

	par->open_count--;
	mutex_unlock(&par->open_lock);
	return 0;
}