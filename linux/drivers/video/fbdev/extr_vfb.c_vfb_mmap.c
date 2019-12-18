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
struct vm_area_struct {int /*<<< orphan*/  vm_pgoff; } ;
struct TYPE_2__ {scalar_t__ smem_start; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */
 int remap_vmalloc_range (struct vm_area_struct*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfb_mmap(struct fb_info *info,
		    struct vm_area_struct *vma)
{
	return remap_vmalloc_range(vma, (void *)info->fix.smem_start, vma->vm_pgoff);
}