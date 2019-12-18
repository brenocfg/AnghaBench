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
struct rtl8169_private {int /*<<< orphan*/  dev; } ;
struct page {int dummy; } ;
struct device {int dummy; } ;
struct RxDesc {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  R8169_RX_BUF_SIZE ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int dev_to_node (struct device*) ; 
 int /*<<< orphan*/  dma_map_page (struct device*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_err (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl8169_mark_to_asic (struct RxDesc*) ; 
 struct device* tp_to_dev (struct rtl8169_private*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *rtl8169_alloc_rx_data(struct rtl8169_private *tp,
					  struct RxDesc *desc)
{
	struct device *d = tp_to_dev(tp);
	int node = dev_to_node(d);
	dma_addr_t mapping;
	struct page *data;

	data = alloc_pages_node(node, GFP_KERNEL, get_order(R8169_RX_BUF_SIZE));
	if (!data)
		return NULL;

	mapping = dma_map_page(d, data, 0, R8169_RX_BUF_SIZE, DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(d, mapping))) {
		if (net_ratelimit())
			netif_err(tp, drv, tp->dev, "Failed to map RX DMA!\n");
		__free_pages(data, get_order(R8169_RX_BUF_SIZE));
		return NULL;
	}

	desc->addr = cpu_to_le64(mapping);
	rtl8169_mark_to_asic(desc);

	return data;
}