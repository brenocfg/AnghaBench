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
struct xgene_enet_raw_desc16 {int /*<<< orphan*/  m1; } ;
struct xgene_enet_desc_ring {int slots; struct xgene_enet_raw_desc16* raw_desc16; scalar_t__* rx_skb; int /*<<< orphan*/  ndev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATAADDR ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GET_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGENE_ENET_MAX_MTU ; 
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct device* ndev_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_enet_delete_bufpool(struct xgene_enet_desc_ring *buf_pool)
{
	struct device *dev = ndev_to_dev(buf_pool->ndev);
	struct xgene_enet_raw_desc16 *raw_desc;
	dma_addr_t dma_addr;
	int i;

	/* Free up the buffers held by hardware */
	for (i = 0; i < buf_pool->slots; i++) {
		if (buf_pool->rx_skb[i]) {
			dev_kfree_skb_any(buf_pool->rx_skb[i]);

			raw_desc = &buf_pool->raw_desc16[i];
			dma_addr = GET_VAL(DATAADDR, le64_to_cpu(raw_desc->m1));
			dma_unmap_single(dev, dma_addr, XGENE_ENET_MAX_MTU,
					 DMA_FROM_DEVICE);
		}
	}
}