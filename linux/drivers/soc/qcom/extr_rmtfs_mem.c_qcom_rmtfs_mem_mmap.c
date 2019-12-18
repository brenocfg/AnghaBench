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
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int /*<<< orphan*/  vm_page_prot; } ;
struct qcom_rmtfs_mem {scalar_t__ size; int addr; int /*<<< orphan*/  dev; } ;
struct file {struct qcom_rmtfs_mem* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int remap_pfn_range (struct vm_area_struct*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_rmtfs_mem_mmap(struct file *filep, struct vm_area_struct *vma)
{
	struct qcom_rmtfs_mem *rmtfs_mem = filep->private_data;

	if (vma->vm_end - vma->vm_start > rmtfs_mem->size) {
		dev_dbg(&rmtfs_mem->dev,
			"vm_end[%lu] - vm_start[%lu] [%lu] > mem->size[%pa]\n",
			vma->vm_end, vma->vm_start,
			(vma->vm_end - vma->vm_start), &rmtfs_mem->size);
		return -EINVAL;
	}

	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	return remap_pfn_range(vma,
			       vma->vm_start,
			       rmtfs_mem->addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}