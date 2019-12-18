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
struct vm_area_struct {size_t vm_end; size_t vm_start; int /*<<< orphan*/  vm_page_prot; } ;
struct tee_shm {int flags; int paddr; } ;
struct dma_buf {struct tee_shm* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int TEE_SHM_REGISTER ; 
 int remap_pfn_range (struct vm_area_struct*,size_t,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tee_shm_op_mmap(struct dma_buf *dmabuf, struct vm_area_struct *vma)
{
	struct tee_shm *shm = dmabuf->priv;
	size_t size = vma->vm_end - vma->vm_start;

	/* Refuse sharing shared memory provided by application */
	if (shm->flags & TEE_SHM_REGISTER)
		return -EINVAL;

	return remap_pfn_range(vma, vma->vm_start, shm->paddr >> PAGE_SHIFT,
			       size, vma->vm_page_prot);
}