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
struct dma_ops_domain {int /*<<< orphan*/  iovad; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned int __roundup_pow_of_two (unsigned int) ; 
 int /*<<< orphan*/  free_iova_fast (int /*<<< orphan*/ *,unsigned long,unsigned int) ; 

__attribute__((used)) static void dma_ops_free_iova(struct dma_ops_domain *dma_dom,
			      unsigned long address,
			      unsigned int pages)
{
	pages = __roundup_pow_of_two(pages);
	address >>= PAGE_SHIFT;

	free_iova_fast(&dma_dom->iovad, address, pages);
}