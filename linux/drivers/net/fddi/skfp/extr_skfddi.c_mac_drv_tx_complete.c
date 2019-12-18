#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct TYPE_8__ {scalar_t__ dma_addr; struct sk_buff* skb; } ;
struct s_smt_fp_txd {TYPE_4__ txd_os; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_6__ {TYPE_1__ gen; } ;
struct TYPE_7__ {TYPE_2__ MacStat; int /*<<< orphan*/  pdev; } ;
struct s_smc {TYPE_3__ os; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void mac_drv_tx_complete(struct s_smc *smc, volatile struct s_smt_fp_txd *txd)
{
	struct sk_buff *skb;

	pr_debug("entering mac_drv_tx_complete\n");
	// Check if this TxD points to a skb

	if (!(skb = txd->txd_os.skb)) {
		pr_debug("TXD with no skb assigned.\n");
		return;
	}
	txd->txd_os.skb = NULL;

	// release the DMA mapping
	pci_unmap_single(&smc->os.pdev, txd->txd_os.dma_addr,
			 skb->len, PCI_DMA_TODEVICE);
	txd->txd_os.dma_addr = 0;

	smc->os.MacStat.gen.tx_packets++;	// Count transmitted packets.
	smc->os.MacStat.gen.tx_bytes+=skb->len;	// Count bytes

	// free the skb
	dev_kfree_skb_irq(skb);

	pr_debug("leaving mac_drv_tx_complete\n");
}