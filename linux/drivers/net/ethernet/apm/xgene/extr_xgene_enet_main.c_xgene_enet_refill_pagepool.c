#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct xgene_enet_raw_desc16 {int /*<<< orphan*/  m1; } ;
struct xgene_enet_pdata {TYPE_1__* ring_ops; } ;
struct xgene_enet_desc_ring {int slots; int tail; struct page** frag_page; struct xgene_enet_raw_desc16* raw_desc16; struct net_device* ndev; } ;
struct page {int dummy; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* wr_cmd ) (struct xgene_enet_desc_ring*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUFDATALEN ; 
 int /*<<< orphan*/  COHERENT ; 
 int /*<<< orphan*/  DATAADDR ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SET_BIT (int /*<<< orphan*/ ) ; 
 int SET_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 struct page* dev_alloc_page () ; 
 int /*<<< orphan*/  dma_map_page (struct device*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 struct device* ndev_to_dev (struct net_device*) ; 
 struct xgene_enet_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  stub1 (struct xgene_enet_desc_ring*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xgene_enet_set_data_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_enet_refill_pagepool(struct xgene_enet_desc_ring *buf_pool,
				      u32 nbuf)
{
	struct xgene_enet_raw_desc16 *raw_desc;
	struct xgene_enet_pdata *pdata;
	struct net_device *ndev;
	dma_addr_t dma_addr;
	struct device *dev;
	struct page *page;
	u32 slots, tail;
	u16 hw_len;
	int i;

	if (unlikely(!buf_pool))
		return 0;

	ndev = buf_pool->ndev;
	pdata = netdev_priv(ndev);
	dev = ndev_to_dev(ndev);
	slots = buf_pool->slots - 1;
	tail = buf_pool->tail;

	for (i = 0; i < nbuf; i++) {
		raw_desc = &buf_pool->raw_desc16[tail];

		page = dev_alloc_page();
		if (unlikely(!page))
			return -ENOMEM;

		dma_addr = dma_map_page(dev, page, 0,
					PAGE_SIZE, DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(dev, dma_addr))) {
			put_page(page);
			return -ENOMEM;
		}

		hw_len = xgene_enet_set_data_len(PAGE_SIZE);
		raw_desc->m1 = cpu_to_le64(SET_VAL(DATAADDR, dma_addr) |
					   SET_VAL(BUFDATALEN, hw_len) |
					   SET_BIT(COHERENT));

		buf_pool->frag_page[tail] = page;
		tail = (tail + 1) & slots;
	}

	pdata->ring_ops->wr_cmd(buf_pool, nbuf);
	buf_pool->tail = tail;

	return 0;
}