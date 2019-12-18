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
struct vm_area_struct {size_t vm_pgoff; struct tcmu_dev* vm_private_data; } ;
struct uio_info {TYPE_1__* mem; } ;
struct tcmu_dev {struct uio_info uio_info; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 size_t MAX_UIO_MAPS ; 

__attribute__((used)) static int tcmu_find_mem_index(struct vm_area_struct *vma)
{
	struct tcmu_dev *udev = vma->vm_private_data;
	struct uio_info *info = &udev->uio_info;

	if (vma->vm_pgoff < MAX_UIO_MAPS) {
		if (info->mem[vma->vm_pgoff].size == 0)
			return -1;
		return (int)vma->vm_pgoff;
	}
	return -1;
}