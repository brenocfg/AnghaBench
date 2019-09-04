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
struct qlcnic_skb_frag {long long dma; int /*<<< orphan*/  length; } ;
struct qlcnic_host_tx_ring {int num_desc; int /*<<< orphan*/  tx_clean_lock; struct qlcnic_cmd_buffer* cmd_buf_arr; } ;
struct qlcnic_cmd_buffer {int frag_count; int /*<<< orphan*/ * skb; struct qlcnic_skb_frag* frag_array; } ;
struct qlcnic_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void qlcnic_release_tx_buffers(struct qlcnic_adapter *adapter,
			       struct qlcnic_host_tx_ring *tx_ring)
{
	struct qlcnic_cmd_buffer *cmd_buf;
	struct qlcnic_skb_frag *buffrag;
	int i, j;

	spin_lock(&tx_ring->tx_clean_lock);

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

	spin_unlock(&tx_ring->tx_clean_lock);
}