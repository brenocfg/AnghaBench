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
struct TYPE_4__ {int /*<<< orphan*/  (* SetStartAddress ) (TYPE_2__*,unsigned int) ;} ;
struct riva_par {TYPE_2__ riva; } ;
struct fb_var_screeninfo {unsigned int yoffset; unsigned int xoffset; } ;
struct TYPE_3__ {unsigned int line_length; } ;
struct fb_info {TYPE_1__ fix; struct riva_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static int rivafb_pan_display(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
	struct riva_par *par = info->par;
	unsigned int base;

	NVTRACE_ENTER();
	base = var->yoffset * info->fix.line_length + var->xoffset;
	par->riva.SetStartAddress(&par->riva, base);
	NVTRACE_LEAVE();
	return 0;
}