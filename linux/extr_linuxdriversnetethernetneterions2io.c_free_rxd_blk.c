#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct swStat {int /*<<< orphan*/  mem_freed; } ;
struct stat_block {struct swStat sw_stat; } ;
struct sk_buff {scalar_t__ truesize; } ;
struct mac_info {TYPE_3__* rings; struct stat_block* stats_info; } ;
struct s2io_nic {size_t rxd_mode; int /*<<< orphan*/  pdev; struct mac_info mac_control; struct net_device* dev; } ;
struct net_device {scalar_t__ mtu; } ;
struct RxD_t {scalar_t__ Host_Control; } ;
struct RxD3 {scalar_t__ Buffer2_ptr; scalar_t__ Buffer1_ptr; scalar_t__ Buffer0_ptr; } ;
struct RxD1 {scalar_t__ Buffer0_ptr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int rx_bufs_left; TYPE_2__* rx_blocks; } ;
struct TYPE_5__ {TYPE_1__* rxds; } ;
struct TYPE_4__ {struct RxD_t* virt_addr; } ;

/* Variables and functions */
 scalar_t__ BUF0_LEN ; 
 scalar_t__ BUF1_LEN ; 
 scalar_t__ HEADER_802_2_SIZE ; 
 scalar_t__ HEADER_ETHERNET_II_802_3_SIZE ; 
 scalar_t__ HEADER_SNAP_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 size_t RXD_MODE_1 ; 
 size_t RXD_MODE_3B ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct RxD_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int* rxd_count ; 

__attribute__((used)) static void free_rxd_blk(struct s2io_nic *sp, int ring_no, int blk)
{
	struct net_device *dev = sp->dev;
	int j;
	struct sk_buff *skb;
	struct RxD_t *rxdp;
	struct RxD1 *rxdp1;
	struct RxD3 *rxdp3;
	struct mac_info *mac_control = &sp->mac_control;
	struct stat_block *stats = mac_control->stats_info;
	struct swStat *swstats = &stats->sw_stat;

	for (j = 0 ; j < rxd_count[sp->rxd_mode]; j++) {
		rxdp = mac_control->rings[ring_no].
			rx_blocks[blk].rxds[j].virt_addr;
		skb = (struct sk_buff *)((unsigned long)rxdp->Host_Control);
		if (!skb)
			continue;
		if (sp->rxd_mode == RXD_MODE_1) {
			rxdp1 = (struct RxD1 *)rxdp;
			pci_unmap_single(sp->pdev,
					 (dma_addr_t)rxdp1->Buffer0_ptr,
					 dev->mtu +
					 HEADER_ETHERNET_II_802_3_SIZE +
					 HEADER_802_2_SIZE + HEADER_SNAP_SIZE,
					 PCI_DMA_FROMDEVICE);
			memset(rxdp, 0, sizeof(struct RxD1));
		} else if (sp->rxd_mode == RXD_MODE_3B) {
			rxdp3 = (struct RxD3 *)rxdp;
			pci_unmap_single(sp->pdev,
					 (dma_addr_t)rxdp3->Buffer0_ptr,
					 BUF0_LEN,
					 PCI_DMA_FROMDEVICE);
			pci_unmap_single(sp->pdev,
					 (dma_addr_t)rxdp3->Buffer1_ptr,
					 BUF1_LEN,
					 PCI_DMA_FROMDEVICE);
			pci_unmap_single(sp->pdev,
					 (dma_addr_t)rxdp3->Buffer2_ptr,
					 dev->mtu + 4,
					 PCI_DMA_FROMDEVICE);
			memset(rxdp, 0, sizeof(struct RxD3));
		}
		swstats->mem_freed += skb->truesize;
		dev_kfree_skb(skb);
		mac_control->rings[ring_no].rx_bufs_left -= 1;
	}
}