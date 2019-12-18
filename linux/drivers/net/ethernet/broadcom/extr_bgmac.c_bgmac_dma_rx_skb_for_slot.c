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
struct device {int dummy; } ;
struct bgmac_slot_info {int /*<<< orphan*/  dma_addr; void* buf; } ;
struct bgmac_rx_header {void* flags; void* len; } ;
struct bgmac {int /*<<< orphan*/  net_dev; struct device* dma_dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGMAC_RX_ALLOC_SIZE ; 
 int BGMAC_RX_BUF_OFFSET ; 
 int /*<<< orphan*/  BGMAC_RX_BUF_SIZE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 void* netdev_alloc_frag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_head_page (void*) ; 

__attribute__((used)) static int bgmac_dma_rx_skb_for_slot(struct bgmac *bgmac,
				     struct bgmac_slot_info *slot)
{
	struct device *dma_dev = bgmac->dma_dev;
	dma_addr_t dma_addr;
	struct bgmac_rx_header *rx;
	void *buf;

	/* Alloc skb */
	buf = netdev_alloc_frag(BGMAC_RX_ALLOC_SIZE);
	if (!buf)
		return -ENOMEM;

	/* Poison - if everything goes fine, hardware will overwrite it */
	rx = buf + BGMAC_RX_BUF_OFFSET;
	rx->len = cpu_to_le16(0xdead);
	rx->flags = cpu_to_le16(0xbeef);

	/* Map skb for the DMA */
	dma_addr = dma_map_single(dma_dev, buf + BGMAC_RX_BUF_OFFSET,
				  BGMAC_RX_BUF_SIZE, DMA_FROM_DEVICE);
	if (dma_mapping_error(dma_dev, dma_addr)) {
		netdev_err(bgmac->net_dev, "DMA mapping error\n");
		put_page(virt_to_head_page(buf));
		return -ENOMEM;
	}

	/* Update the slot */
	slot->buf = buf;
	slot->dma_addr = dma_addr;

	return 0;
}