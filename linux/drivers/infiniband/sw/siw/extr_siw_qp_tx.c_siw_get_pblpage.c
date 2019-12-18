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
typedef  scalar_t__ u64 ;
struct siw_pbl {int dummy; } ;
struct siw_mem {scalar_t__ va; struct siw_pbl* pbl; } ;
struct page {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ siw_pbl_get_buffer (struct siw_pbl*,scalar_t__,int /*<<< orphan*/ *,int*) ; 
 struct page* virt_to_page (scalar_t__) ; 

__attribute__((used)) static struct page *siw_get_pblpage(struct siw_mem *mem, u64 addr, int *idx)
{
	struct siw_pbl *pbl = mem->pbl;
	u64 offset = addr - mem->va;
	dma_addr_t paddr = siw_pbl_get_buffer(pbl, offset, NULL, idx);

	if (paddr)
		return virt_to_page(paddr);

	return NULL;
}