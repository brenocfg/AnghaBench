#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rx_queue {int index; int rx_ring_size; int rx_desc_area_size; scalar_t__ rx_desc_dma; struct rx_desc* rx_desc_area; int /*<<< orphan*/ * rx_skb; scalar_t__ rx_used_desc; scalar_t__ rx_curr_desc; scalar_t__ rx_desc_count; } ;
struct rx_desc {scalar_t__ next_desc_ptr; } ;
struct mv643xx_eth_private {int rx_ring_size; int rx_desc_sram_size; TYPE_2__* dev; scalar_t__ rx_desc_sram_addr; struct rx_queue* rxq; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rx_desc* dma_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,struct rx_desc*,scalar_t__) ; 
 struct rx_desc* ioremap (scalar_t__,int) ; 
 int /*<<< orphan*/  iounmap (struct rx_desc*) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rx_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*,int) ; 

__attribute__((used)) static int rxq_init(struct mv643xx_eth_private *mp, int index)
{
	struct rx_queue *rxq = mp->rxq + index;
	struct rx_desc *rx_desc;
	int size;
	int i;

	rxq->index = index;

	rxq->rx_ring_size = mp->rx_ring_size;

	rxq->rx_desc_count = 0;
	rxq->rx_curr_desc = 0;
	rxq->rx_used_desc = 0;

	size = rxq->rx_ring_size * sizeof(struct rx_desc);

	if (index == 0 && size <= mp->rx_desc_sram_size) {
		rxq->rx_desc_area = ioremap(mp->rx_desc_sram_addr,
						mp->rx_desc_sram_size);
		rxq->rx_desc_dma = mp->rx_desc_sram_addr;
	} else {
		rxq->rx_desc_area = dma_alloc_coherent(mp->dev->dev.parent,
						       size, &rxq->rx_desc_dma,
						       GFP_KERNEL);
	}

	if (rxq->rx_desc_area == NULL) {
		netdev_err(mp->dev,
			   "can't allocate rx ring (%d bytes)\n", size);
		goto out;
	}
	memset(rxq->rx_desc_area, 0, size);

	rxq->rx_desc_area_size = size;
	rxq->rx_skb = kcalloc(rxq->rx_ring_size, sizeof(*rxq->rx_skb),
				    GFP_KERNEL);
	if (rxq->rx_skb == NULL)
		goto out_free;

	rx_desc = rxq->rx_desc_area;
	for (i = 0; i < rxq->rx_ring_size; i++) {
		int nexti;

		nexti = i + 1;
		if (nexti == rxq->rx_ring_size)
			nexti = 0;

		rx_desc[i].next_desc_ptr = rxq->rx_desc_dma +
					nexti * sizeof(struct rx_desc);
	}

	return 0;


out_free:
	if (index == 0 && size <= mp->rx_desc_sram_size)
		iounmap(rxq->rx_desc_area);
	else
		dma_free_coherent(mp->dev->dev.parent, size,
				  rxq->rx_desc_area,
				  rxq->rx_desc_dma);

out:
	return -ENOMEM;
}