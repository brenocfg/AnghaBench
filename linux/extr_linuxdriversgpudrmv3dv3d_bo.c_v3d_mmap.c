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
struct vm_area_struct {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int drm_gem_mmap (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  v3d_set_mmap_vma_flags (struct vm_area_struct*) ; 

int v3d_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int ret;

	ret = drm_gem_mmap(filp, vma);
	if (ret)
		return ret;

	v3d_set_mmap_vma_flags(vma);

	return ret;
}