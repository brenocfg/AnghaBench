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
struct net_device {int dummy; } ;
struct ftmac100_rxdes {int dummy; } ;
struct ftmac100 {int /*<<< orphan*/  dev; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftmac100_rxdes_set_buffer_size (struct ftmac100_rxdes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftmac100_rxdes_set_dma_addr (struct ftmac100_rxdes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftmac100_rxdes_set_dma_own (struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_rxdes_set_page (struct ftmac100_rxdes*,struct page*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftmac100_alloc_rx_page(struct ftmac100 *priv,
				  struct ftmac100_rxdes *rxdes, gfp_t gfp)
{
	struct net_device *netdev = priv->netdev;
	struct page *page;
	dma_addr_t map;

	page = alloc_page(gfp);
	if (!page) {
		if (net_ratelimit())
			netdev_err(netdev, "failed to allocate rx page\n");
		return -ENOMEM;
	}

	map = dma_map_page(priv->dev, page, 0, RX_BUF_SIZE, DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(priv->dev, map))) {
		if (net_ratelimit())
			netdev_err(netdev, "failed to map rx page\n");
		__free_page(page);
		return -ENOMEM;
	}

	ftmac100_rxdes_set_page(rxdes, page);
	ftmac100_rxdes_set_dma_addr(rxdes, map);
	ftmac100_rxdes_set_buffer_size(rxdes, RX_BUF_SIZE);
	ftmac100_rxdes_set_dma_own(rxdes);
	return 0;
}