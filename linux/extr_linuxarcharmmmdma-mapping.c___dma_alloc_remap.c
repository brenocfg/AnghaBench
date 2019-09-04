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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int VM_ARM_DMA_CONSISTENT ; 
 int VM_USERMAP ; 
 void* dma_common_contiguous_remap (struct page*,size_t,int,int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static void *
__dma_alloc_remap(struct page *page, size_t size, gfp_t gfp, pgprot_t prot,
	const void *caller)
{
	/*
	 * DMA allocation can be mapped to user space, so lets
	 * set VM_USERMAP flags too.
	 */
	return dma_common_contiguous_remap(page, size,
			VM_ARM_DMA_CONSISTENT | VM_USERMAP,
			prot, caller);
}