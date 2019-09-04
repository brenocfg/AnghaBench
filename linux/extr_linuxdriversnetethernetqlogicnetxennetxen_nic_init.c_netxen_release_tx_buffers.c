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
struct nx_host_tx_ring {int num_desc; struct netxen_cmd_buffer* cmd_buf_arr; } ;
struct netxen_skb_frag {long long dma; int /*<<< orphan*/  length; } ;
struct netxen_cmd_buffer {int frag_count; int /*<<< orphan*/ * skb; struct netxen_skb_frag* frag_array; } ;
struct netxen_adapter {int /*<<< orphan*/  tx_clean_lock; int /*<<< orphan*/  pdev; struct nx_host_tx_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void netxen_release_tx_buffers(struct netxen_adapter *adapter)
{
	struct netxen_cmd_buffer *cmd_buf;
	struct netxen_skb_frag *buffrag;
	int i, j;
	struct nx_host_tx_ring *tx_ring = adapter->tx_ring;

	spin_lock_bh(&adapter->tx_clean_lock);
	cmd_buf = tx_ring->cmd_buf_arr;
	for (i = 0; i < tx_ring->num_desc; i++) {
		buffrag = cmd_buf->frag_array;
		if (buffrag->dma) {
			pci_unmap_single(adapter->pdev, buffrag->dma,
					 buffrag->length, PCI_DMA_TODEVICE);
			buffrag->dma = 0ULL;
		}
		for (j = 1; j < cmd_buf->frag_count; j++) {
			buffrag++;
			if (buffrag->dma) {
				pci_unmap_page(adapter->pdev, buffrag->dma,
					       buffrag->length,
					       PCI_DMA_TODEVICE);
				buffrag->dma = 0ULL;
			}
		}
		if (cmd_buf->skb) {
			dev_kfree_skb_any(cmd_buf->skb);
			cmd_buf->skb = NULL;
		}
		cmd_buf++;
	}
	spin_unlock_bh(&adapter->tx_clean_lock);
}