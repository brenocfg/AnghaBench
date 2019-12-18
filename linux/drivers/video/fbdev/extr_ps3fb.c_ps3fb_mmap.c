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
struct vm_area_struct {int vm_pgoff; int /*<<< orphan*/  vm_start; } ;
struct TYPE_2__ {scalar_t__ smem_start; int /*<<< orphan*/  smem_len; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int vm_iomap_memory (struct vm_area_struct*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps3fb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	int r;

	r = vm_iomap_memory(vma, info->fix.smem_start, info->fix.smem_len);

	dev_dbg(info->device, "ps3fb: mmap framebuffer P(%lx)->V(%lx)\n",
		info->fix.smem_start + (vma->vm_pgoff << PAGE_SHIFT),
		vma->vm_start);

	return r;
}