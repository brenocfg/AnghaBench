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
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct qtnf_topaz_rx_bd {void* info; void* addr; } ;
struct TYPE_2__ {size_t rx_bd_w_index; int /*<<< orphan*/  pdev; struct sk_buff** rx_skb; } ;
struct qtnf_pcie_topaz_state {TYPE_1__ base; struct qtnf_topaz_rx_bd* rx_bd_vbase; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int QTN_BD_EMPTY ; 
 int QTN_HOST_LO32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKB_BUF_SIZE ; 
 struct sk_buff* __netdev_alloc_skb_ip_align (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
topaz_skb2rbd_attach(struct qtnf_pcie_topaz_state *ts, u16 index, u32 wrap)
{
	struct qtnf_topaz_rx_bd *rxbd = &ts->rx_bd_vbase[index];
	struct sk_buff *skb;
	dma_addr_t paddr;

	skb = __netdev_alloc_skb_ip_align(NULL, SKB_BUF_SIZE, GFP_ATOMIC);
	if (!skb) {
		ts->base.rx_skb[index] = NULL;
		return -ENOMEM;
	}

	ts->base.rx_skb[index] = skb;

	paddr = pci_map_single(ts->base.pdev, skb->data,
			       SKB_BUF_SIZE, PCI_DMA_FROMDEVICE);
	if (pci_dma_mapping_error(ts->base.pdev, paddr)) {
		pr_err("skb mapping error: %pad\n", &paddr);
		return -ENOMEM;
	}

	rxbd->addr = cpu_to_le32(QTN_HOST_LO32(paddr));
	rxbd->info = cpu_to_le32(QTN_BD_EMPTY | wrap);

	ts->base.rx_bd_w_index = index;

	return 0;
}