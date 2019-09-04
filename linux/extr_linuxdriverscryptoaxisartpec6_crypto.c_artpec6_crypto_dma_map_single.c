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
struct artpec6_crypto_req_common {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 uintptr_t PAGE_MASK ; 
 int artpec6_crypto_dma_map_page (struct artpec6_crypto_req_common*,struct page*,size_t,size_t,int,int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static int
artpec6_crypto_dma_map_single(struct artpec6_crypto_req_common *common,
			      void *ptr, size_t size,
			      enum dma_data_direction dir,
			      dma_addr_t *dma_addr_out)
{
	struct page *page = virt_to_page(ptr);
	size_t offset = (uintptr_t)ptr & ~PAGE_MASK;

	return artpec6_crypto_dma_map_page(common, page, offset, size, dir,
					  dma_addr_out);
}