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
typedef  int u32 ;
struct tg3 {int /*<<< orphan*/  pdev; } ;
struct skb_shared_info {int dummy; } ;
struct ring_info {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 unsigned int SKB_DATA_ALIGN (int) ; 
 int TG3_RX_OFFSET (struct tg3*) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct ring_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_frag_free (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tg3_rx_data_free(struct tg3 *tp, struct ring_info *ri, u32 map_sz)
{
	unsigned int skb_size = SKB_DATA_ALIGN(map_sz + TG3_RX_OFFSET(tp)) +
		   SKB_DATA_ALIGN(sizeof(struct skb_shared_info));

	if (!ri->data)
		return;

	pci_unmap_single(tp->pdev, dma_unmap_addr(ri, mapping),
			 map_sz, PCI_DMA_FROMDEVICE);
	tg3_frag_free(skb_size <= PAGE_SIZE, ri->data);
	ri->data = NULL;
}