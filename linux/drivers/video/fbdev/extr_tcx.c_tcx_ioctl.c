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
struct tcx_par {scalar_t__ lowdepth; } ;
struct TYPE_2__ {int /*<<< orphan*/  smem_len; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBTYPE_TCXCOLOR ; 
 int sbusfb_ioctl_helper (unsigned int,unsigned long,struct fb_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcx_ioctl(struct fb_info *info, unsigned int cmd,
		     unsigned long arg)
{
	struct tcx_par *par = (struct tcx_par *) info->par;

	return sbusfb_ioctl_helper(cmd, arg, info,
				   FBTYPE_TCXCOLOR,
				   (par->lowdepth ? 8 : 24),
				   info->fix.smem_len);
}