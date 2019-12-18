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
struct qib_user_sdma_queue {int /*<<< orphan*/  header_cache; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t QIB_USER_SDMA_EXP_HEADER_LENGTH ; 
 void* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *qib_user_sdma_alloc_header(struct qib_user_sdma_queue *pq,
				size_t len, dma_addr_t *dma_addr)
{
	void *hdr;

	if (len == QIB_USER_SDMA_EXP_HEADER_LENGTH)
		hdr = dma_pool_alloc(pq->header_cache, GFP_KERNEL,
					     dma_addr);
	else
		hdr = NULL;

	if (!hdr) {
		hdr = kmalloc(len, GFP_KERNEL);
		if (!hdr)
			return NULL;

		*dma_addr = 0;
	}

	return hdr;
}