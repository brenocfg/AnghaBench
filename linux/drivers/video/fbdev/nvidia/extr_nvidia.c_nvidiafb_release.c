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
struct nvidia_par {int open_count; int /*<<< orphan*/  initial_state; } ;
struct fb_info {struct nvidia_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvidia_write_regs (struct nvidia_par*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_vga_x86 (struct nvidia_par*) ; 

__attribute__((used)) static int nvidiafb_release(struct fb_info *info, int user)
{
	struct nvidia_par *par = info->par;
	int err = 0;

	if (!par->open_count) {
		err = -EINVAL;
		goto done;
	}

	if (par->open_count == 1) {
		nvidia_write_regs(par, &par->initial_state);
		restore_vga_x86(par);
	}

	par->open_count--;
done:
	return err;
}