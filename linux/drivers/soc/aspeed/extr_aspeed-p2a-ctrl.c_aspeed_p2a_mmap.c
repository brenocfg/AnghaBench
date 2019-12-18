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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; scalar_t__ vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct file {struct aspeed_p2a_user* private_data; } ;
struct aspeed_p2a_user {struct aspeed_p2a_ctrl* parent; } ;
struct aspeed_p2a_ctrl {int mem_base; scalar_t__ mem_size; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,unsigned long,scalar_t__,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aspeed_p2a_mmap(struct file *file, struct vm_area_struct *vma)
{
	unsigned long vsize;
	pgprot_t prot;
	struct aspeed_p2a_user *priv = file->private_data;
	struct aspeed_p2a_ctrl *ctrl = priv->parent;

	if (ctrl->mem_base == 0 && ctrl->mem_size == 0)
		return -EINVAL;

	vsize = vma->vm_end - vma->vm_start;
	prot = vma->vm_page_prot;

	if (vma->vm_pgoff + vsize > ctrl->mem_base + ctrl->mem_size)
		return -EINVAL;

	/* ast2400/2500 AHB accesses are not cache coherent */
	prot = pgprot_noncached(prot);

	if (remap_pfn_range(vma, vma->vm_start,
		(ctrl->mem_base >> PAGE_SHIFT) + vma->vm_pgoff,
		vsize, prot))
		return -EAGAIN;

	return 0;
}