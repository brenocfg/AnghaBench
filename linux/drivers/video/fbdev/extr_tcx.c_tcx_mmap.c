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
struct vm_area_struct {int dummy; } ;
struct tcx_par {int /*<<< orphan*/  which_io; int /*<<< orphan*/  mmap_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ par; } ;

/* Variables and functions */
 int sbusfb_mmap_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int tcx_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct tcx_par *par = (struct tcx_par *)info->par;

	return sbusfb_mmap_helper(par->mmap_map,
				  info->fix.smem_start, info->fix.smem_len,
				  par->which_io, vma);
}