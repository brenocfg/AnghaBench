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
struct TYPE_7__ {void* buffer_addr; } ;
union e1000_rx_desc_extended {TYPE_2__ read; } ;
typedef  int u64 ;
typedef  int u32 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {scalar_t__ data; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct e1000_tx_desc {TYPE_5__ upper; TYPE_4__ lower; void* buffer_addr; } ;
struct e1000_ring {int count; int size; TYPE_3__* buffer_info; scalar_t__ dma; scalar_t__ next_to_clean; scalar_t__ next_to_use; void* desc; } ;
struct TYPE_6__ {int mc_filter_type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct e1000_buffer {int dummy; } ;
struct e1000_adapter {int flags2; struct e1000_hw hw; struct pci_dev* pdev; struct e1000_ring test_rx_ring; struct e1000_ring test_tx_ring; } ;
struct TYPE_8__ {int length; void* dma; struct sk_buff* skb; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int E1000_COLD_SHIFT ; 
 int E1000_COLLISION_DISTANCE ; 
 int E1000_COLLISION_THRESHOLD ; 
 int E1000_CT_SHIFT ; 
 int E1000_DEFAULT_RXD ; 
 int E1000_DEFAULT_TXD ; 
 int E1000_RCTL_BAM ; 
 int E1000_RCTL_EN ; 
 int E1000_RCTL_LBM_NO ; 
 int E1000_RCTL_LPE ; 
 int E1000_RCTL_MO_SHIFT ; 
 int E1000_RCTL_MPE ; 
 int E1000_RCTL_RDMTS_HALF ; 
 int E1000_RCTL_SBP ; 
 int E1000_RCTL_SECRC ; 
 int E1000_RCTL_SZ_2048 ; 
 int E1000_RCTL_UPE ; 
 union e1000_rx_desc_extended* E1000_RX_DESC_EXT (struct e1000_ring,int) ; 
 int E1000_TCTL_EN ; 
 int E1000_TCTL_MULR ; 
 int E1000_TCTL_PSP ; 
 int E1000_TXD_CMD_EOP ; 
 int E1000_TXD_CMD_IFCS ; 
 int E1000_TXD_CMD_RS ; 
 struct e1000_tx_desc* E1000_TX_DESC (struct e1000_ring,int) ; 
 int FLAG2_NO_DISABLE_RX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  RDBAH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  TDBAH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDT (int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 void* cpu_to_le64 (void*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 void* dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  e1000_free_desc_rings (struct e1000_adapter*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int e1000_setup_desc_rings(struct e1000_adapter *adapter)
{
	struct e1000_ring *tx_ring = &adapter->test_tx_ring;
	struct e1000_ring *rx_ring = &adapter->test_rx_ring;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_hw *hw = &adapter->hw;
	u32 rctl;
	int i;
	int ret_val;

	/* Setup Tx descriptor ring and Tx buffers */

	if (!tx_ring->count)
		tx_ring->count = E1000_DEFAULT_TXD;

	tx_ring->buffer_info = kcalloc(tx_ring->count,
				       sizeof(struct e1000_buffer), GFP_KERNEL);
	if (!tx_ring->buffer_info) {
		ret_val = 1;
		goto err_nomem;
	}

	tx_ring->size = tx_ring->count * sizeof(struct e1000_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);
	tx_ring->desc = dma_alloc_coherent(&pdev->dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	if (!tx_ring->desc) {
		ret_val = 2;
		goto err_nomem;
	}
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	ew32(TDBAL(0), ((u64)tx_ring->dma & 0x00000000FFFFFFFF));
	ew32(TDBAH(0), ((u64)tx_ring->dma >> 32));
	ew32(TDLEN(0), tx_ring->count * sizeof(struct e1000_tx_desc));
	ew32(TDH(0), 0);
	ew32(TDT(0), 0);
	ew32(TCTL, E1000_TCTL_PSP | E1000_TCTL_EN | E1000_TCTL_MULR |
	     E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT |
	     E1000_COLLISION_DISTANCE << E1000_COLD_SHIFT);

	for (i = 0; i < tx_ring->count; i++) {
		struct e1000_tx_desc *tx_desc = E1000_TX_DESC(*tx_ring, i);
		struct sk_buff *skb;
		unsigned int skb_size = 1024;

		skb = alloc_skb(skb_size, GFP_KERNEL);
		if (!skb) {
			ret_val = 3;
			goto err_nomem;
		}
		skb_put(skb, skb_size);
		tx_ring->buffer_info[i].skb = skb;
		tx_ring->buffer_info[i].length = skb->len;
		tx_ring->buffer_info[i].dma =
		    dma_map_single(&pdev->dev, skb->data, skb->len,
				   DMA_TO_DEVICE);
		if (dma_mapping_error(&pdev->dev,
				      tx_ring->buffer_info[i].dma)) {
			ret_val = 4;
			goto err_nomem;
		}
		tx_desc->buffer_addr = cpu_to_le64(tx_ring->buffer_info[i].dma);
		tx_desc->lower.data = cpu_to_le32(skb->len);
		tx_desc->lower.data |= cpu_to_le32(E1000_TXD_CMD_EOP |
						   E1000_TXD_CMD_IFCS |
						   E1000_TXD_CMD_RS);
		tx_desc->upper.data = 0;
	}

	/* Setup Rx descriptor ring and Rx buffers */

	if (!rx_ring->count)
		rx_ring->count = E1000_DEFAULT_RXD;

	rx_ring->buffer_info = kcalloc(rx_ring->count,
				       sizeof(struct e1000_buffer), GFP_KERNEL);
	if (!rx_ring->buffer_info) {
		ret_val = 5;
		goto err_nomem;
	}

	rx_ring->size = rx_ring->count * sizeof(union e1000_rx_desc_extended);
	rx_ring->desc = dma_alloc_coherent(&pdev->dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);
	if (!rx_ring->desc) {
		ret_val = 6;
		goto err_nomem;
	}
	rx_ring->next_to_use = 0;
	rx_ring->next_to_clean = 0;

	rctl = er32(RCTL);
	if (!(adapter->flags2 & FLAG2_NO_DISABLE_RX))
		ew32(RCTL, rctl & ~E1000_RCTL_EN);
	ew32(RDBAL(0), ((u64)rx_ring->dma & 0xFFFFFFFF));
	ew32(RDBAH(0), ((u64)rx_ring->dma >> 32));
	ew32(RDLEN(0), rx_ring->size);
	ew32(RDH(0), 0);
	ew32(RDT(0), 0);
	rctl = E1000_RCTL_EN | E1000_RCTL_BAM | E1000_RCTL_SZ_2048 |
	    E1000_RCTL_UPE | E1000_RCTL_MPE | E1000_RCTL_LPE |
	    E1000_RCTL_SBP | E1000_RCTL_SECRC |
	    E1000_RCTL_LBM_NO | E1000_RCTL_RDMTS_HALF |
	    (adapter->hw.mac.mc_filter_type << E1000_RCTL_MO_SHIFT);
	ew32(RCTL, rctl);

	for (i = 0; i < rx_ring->count; i++) {
		union e1000_rx_desc_extended *rx_desc;
		struct sk_buff *skb;

		skb = alloc_skb(2048 + NET_IP_ALIGN, GFP_KERNEL);
		if (!skb) {
			ret_val = 7;
			goto err_nomem;
		}
		skb_reserve(skb, NET_IP_ALIGN);
		rx_ring->buffer_info[i].skb = skb;
		rx_ring->buffer_info[i].dma =
		    dma_map_single(&pdev->dev, skb->data, 2048,
				   DMA_FROM_DEVICE);
		if (dma_mapping_error(&pdev->dev,
				      rx_ring->buffer_info[i].dma)) {
			ret_val = 8;
			goto err_nomem;
		}
		rx_desc = E1000_RX_DESC_EXT(*rx_ring, i);
		rx_desc->read.buffer_addr =
		    cpu_to_le64(rx_ring->buffer_info[i].dma);
		memset(skb->data, 0x00, skb->len);
	}

	return 0;

err_nomem:
	e1000_free_desc_rings(adapter);
	return ret_val;
}