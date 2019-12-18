#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct e1000_tx_ring {int count; int size; TYPE_2__* buffer_info; scalar_t__ dma; scalar_t__ next_to_clean; scalar_t__ next_to_use; void* desc; } ;
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct e1000_tx_desc {TYPE_4__ upper; TYPE_3__ lower; void* buffer_addr; } ;
struct e1000_tx_buffer {int dummy; } ;
struct e1000_rx_ring {int count; int size; TYPE_5__* buffer_info; scalar_t__ dma; scalar_t__ next_to_clean; scalar_t__ next_to_use; void* desc; } ;
struct e1000_rx_desc {void* buffer_addr; } ;
struct e1000_rx_buffer {int dummy; } ;
struct e1000_hw {int mc_filter_type; } ;
struct e1000_adapter {struct pci_dev* pdev; struct e1000_rx_ring test_rx_ring; struct e1000_tx_ring test_tx_ring; struct e1000_hw hw; } ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {void* dma; TYPE_1__ rxbuf; } ;
struct TYPE_7__ {int length; void* dma; struct sk_buff* skb; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int E1000_COLD_SHIFT ; 
 int E1000_COLLISION_THRESHOLD ; 
 int E1000_CT_SHIFT ; 
 int E1000_DEFAULT_RXD ; 
 int E1000_DEFAULT_TXD ; 
 int E1000_FDX_COLLISION_DISTANCE ; 
 int E1000_RCTL_BAM ; 
 int E1000_RCTL_EN ; 
 int E1000_RCTL_LBM_NO ; 
 int E1000_RCTL_MO_SHIFT ; 
 int E1000_RCTL_RDMTS_HALF ; 
 int E1000_RCTL_SZ_2048 ; 
 int E1000_RXBUFFER_2048 ; 
 struct e1000_rx_desc* E1000_RX_DESC (struct e1000_rx_ring,int) ; 
 int E1000_TCTL_EN ; 
 int E1000_TCTL_PSP ; 
 int E1000_TXD_CMD_EOP ; 
 int E1000_TXD_CMD_IFCS ; 
 int E1000_TXD_CMD_RPS ; 
 struct e1000_tx_desc* E1000_TX_DESC (struct e1000_tx_ring,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NET_IP_ALIGN ; 
 int NET_SKB_PAD ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  RDBAH ; 
 int /*<<< orphan*/  RDBAL ; 
 int /*<<< orphan*/  RDH ; 
 int /*<<< orphan*/  RDLEN ; 
 int /*<<< orphan*/  RDT ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  TDBAH ; 
 int /*<<< orphan*/  TDBAL ; 
 int /*<<< orphan*/  TDH ; 
 int /*<<< orphan*/  TDLEN ; 
 int /*<<< orphan*/  TDT ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 void* cpu_to_le64 (void*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 void* dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  e1000_free_desc_rings (struct e1000_adapter*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int e1000_setup_desc_rings(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_tx_ring *txdr = &adapter->test_tx_ring;
	struct e1000_rx_ring *rxdr = &adapter->test_rx_ring;
	struct pci_dev *pdev = adapter->pdev;
	u32 rctl;
	int i, ret_val;

	/* Setup Tx descriptor ring and Tx buffers */

	if (!txdr->count)
		txdr->count = E1000_DEFAULT_TXD;

	txdr->buffer_info = kcalloc(txdr->count, sizeof(struct e1000_tx_buffer),
				    GFP_KERNEL);
	if (!txdr->buffer_info) {
		ret_val = 1;
		goto err_nomem;
	}

	txdr->size = txdr->count * sizeof(struct e1000_tx_desc);
	txdr->size = ALIGN(txdr->size, 4096);
	txdr->desc = dma_alloc_coherent(&pdev->dev, txdr->size, &txdr->dma,
					GFP_KERNEL);
	if (!txdr->desc) {
		ret_val = 2;
		goto err_nomem;
	}
	txdr->next_to_use = txdr->next_to_clean = 0;

	ew32(TDBAL, ((u64)txdr->dma & 0x00000000FFFFFFFF));
	ew32(TDBAH, ((u64)txdr->dma >> 32));
	ew32(TDLEN, txdr->count * sizeof(struct e1000_tx_desc));
	ew32(TDH, 0);
	ew32(TDT, 0);
	ew32(TCTL, E1000_TCTL_PSP | E1000_TCTL_EN |
	     E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT |
	     E1000_FDX_COLLISION_DISTANCE << E1000_COLD_SHIFT);

	for (i = 0; i < txdr->count; i++) {
		struct e1000_tx_desc *tx_desc = E1000_TX_DESC(*txdr, i);
		struct sk_buff *skb;
		unsigned int size = 1024;

		skb = alloc_skb(size, GFP_KERNEL);
		if (!skb) {
			ret_val = 3;
			goto err_nomem;
		}
		skb_put(skb, size);
		txdr->buffer_info[i].skb = skb;
		txdr->buffer_info[i].length = skb->len;
		txdr->buffer_info[i].dma =
			dma_map_single(&pdev->dev, skb->data, skb->len,
				       DMA_TO_DEVICE);
		if (dma_mapping_error(&pdev->dev, txdr->buffer_info[i].dma)) {
			ret_val = 4;
			goto err_nomem;
		}
		tx_desc->buffer_addr = cpu_to_le64(txdr->buffer_info[i].dma);
		tx_desc->lower.data = cpu_to_le32(skb->len);
		tx_desc->lower.data |= cpu_to_le32(E1000_TXD_CMD_EOP |
						   E1000_TXD_CMD_IFCS |
						   E1000_TXD_CMD_RPS);
		tx_desc->upper.data = 0;
	}

	/* Setup Rx descriptor ring and Rx buffers */

	if (!rxdr->count)
		rxdr->count = E1000_DEFAULT_RXD;

	rxdr->buffer_info = kcalloc(rxdr->count, sizeof(struct e1000_rx_buffer),
				    GFP_KERNEL);
	if (!rxdr->buffer_info) {
		ret_val = 5;
		goto err_nomem;
	}

	rxdr->size = rxdr->count * sizeof(struct e1000_rx_desc);
	rxdr->desc = dma_alloc_coherent(&pdev->dev, rxdr->size, &rxdr->dma,
					GFP_KERNEL);
	if (!rxdr->desc) {
		ret_val = 6;
		goto err_nomem;
	}
	rxdr->next_to_use = rxdr->next_to_clean = 0;

	rctl = er32(RCTL);
	ew32(RCTL, rctl & ~E1000_RCTL_EN);
	ew32(RDBAL, ((u64)rxdr->dma & 0xFFFFFFFF));
	ew32(RDBAH, ((u64)rxdr->dma >> 32));
	ew32(RDLEN, rxdr->size);
	ew32(RDH, 0);
	ew32(RDT, 0);
	rctl = E1000_RCTL_EN | E1000_RCTL_BAM | E1000_RCTL_SZ_2048 |
		E1000_RCTL_LBM_NO | E1000_RCTL_RDMTS_HALF |
		(hw->mc_filter_type << E1000_RCTL_MO_SHIFT);
	ew32(RCTL, rctl);

	for (i = 0; i < rxdr->count; i++) {
		struct e1000_rx_desc *rx_desc = E1000_RX_DESC(*rxdr, i);
		u8 *buf;

		buf = kzalloc(E1000_RXBUFFER_2048 + NET_SKB_PAD + NET_IP_ALIGN,
			      GFP_KERNEL);
		if (!buf) {
			ret_val = 7;
			goto err_nomem;
		}
		rxdr->buffer_info[i].rxbuf.data = buf;

		rxdr->buffer_info[i].dma =
			dma_map_single(&pdev->dev,
				       buf + NET_SKB_PAD + NET_IP_ALIGN,
				       E1000_RXBUFFER_2048, DMA_FROM_DEVICE);
		if (dma_mapping_error(&pdev->dev, rxdr->buffer_info[i].dma)) {
			ret_val = 8;
			goto err_nomem;
		}
		rx_desc->buffer_addr = cpu_to_le64(rxdr->buffer_info[i].dma);
	}

	return 0;

err_nomem:
	e1000_free_desc_rings(adapter);
	return ret_val;
}