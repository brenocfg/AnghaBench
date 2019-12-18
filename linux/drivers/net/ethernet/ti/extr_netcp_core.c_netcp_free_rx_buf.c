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
struct netcp_intf {int /*<<< orphan*/  rx_pool; int /*<<< orphan*/  dev; int /*<<< orphan*/  ndev_dev; int /*<<< orphan*/ * rx_fdq; } ;
struct knav_dma_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ GET_SW_DATA0 (struct knav_dma_desc*) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_org_pkt_info (int /*<<< orphan*/ *,unsigned int*,struct knav_dma_desc*) ; 
 int /*<<< orphan*/  knav_pool_desc_put (int /*<<< orphan*/ ,struct knav_dma_desc*) ; 
 struct knav_dma_desc* knav_pool_desc_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  knav_queue_pop (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  netcp_frag_free (int,void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void netcp_free_rx_buf(struct netcp_intf *netcp, int fdq)
{
	struct knav_dma_desc *desc;
	unsigned int buf_len, dma_sz;
	dma_addr_t dma;
	void *buf_ptr;

	/* Allocate descriptor */
	while ((dma = knav_queue_pop(netcp->rx_fdq[fdq], &dma_sz))) {
		desc = knav_pool_desc_unmap(netcp->rx_pool, dma, dma_sz);
		if (unlikely(!desc)) {
			dev_err(netcp->ndev_dev, "failed to unmap Rx desc\n");
			continue;
		}

		get_org_pkt_info(&dma, &buf_len, desc);
		/* warning!!!! We are retrieving the virtual ptr in the sw_data
		 * field as a 32bit value. Will not work on 64bit machines
		 */
		buf_ptr = (void *)GET_SW_DATA0(desc);

		if (unlikely(!dma)) {
			dev_err(netcp->ndev_dev, "NULL orig_buff in desc\n");
			knav_pool_desc_put(netcp->rx_pool, desc);
			continue;
		}

		if (unlikely(!buf_ptr)) {
			dev_err(netcp->ndev_dev, "NULL bufptr in desc\n");
			knav_pool_desc_put(netcp->rx_pool, desc);
			continue;
		}

		if (fdq == 0) {
			dma_unmap_single(netcp->dev, dma, buf_len,
					 DMA_FROM_DEVICE);
			netcp_frag_free((buf_len <= PAGE_SIZE), buf_ptr);
		} else {
			dma_unmap_page(netcp->dev, dma, buf_len,
				       DMA_FROM_DEVICE);
			__free_page(buf_ptr);
		}

		knav_pool_desc_put(netcp->rx_pool, desc);
	}
}