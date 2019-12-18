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
struct page {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct nb8800_rx_desc {TYPE_1__ desc; } ;
struct nb8800_rx_buf {unsigned long offset; struct page* page; } ;
struct nb8800_priv {struct nb8800_rx_buf* rx_bufs; struct nb8800_rx_desc* rx_descs; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int L1_CACHE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ *,struct page*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* napi_alloc_frag (int) ; 
 void* netdev_alloc_frag (int) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  skb_free_frag (void*) ; 
 struct page* virt_to_head_page (void*) ; 

__attribute__((used)) static int nb8800_alloc_rx(struct net_device *dev, unsigned int i, bool napi)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	struct nb8800_rx_desc *rxd = &priv->rx_descs[i];
	struct nb8800_rx_buf *rxb = &priv->rx_bufs[i];
	int size = L1_CACHE_ALIGN(RX_BUF_SIZE);
	dma_addr_t dma_addr;
	struct page *page;
	unsigned long offset;
	void *data;

	data = napi ? napi_alloc_frag(size) : netdev_alloc_frag(size);
	if (!data)
		return -ENOMEM;

	page = virt_to_head_page(data);
	offset = data - page_address(page);

	dma_addr = dma_map_page(&dev->dev, page, offset, RX_BUF_SIZE,
				DMA_FROM_DEVICE);

	if (dma_mapping_error(&dev->dev, dma_addr)) {
		skb_free_frag(data);
		return -ENOMEM;
	}

	rxb->page = page;
	rxb->offset = offset;
	rxd->desc.s_addr = dma_addr;

	return 0;
}