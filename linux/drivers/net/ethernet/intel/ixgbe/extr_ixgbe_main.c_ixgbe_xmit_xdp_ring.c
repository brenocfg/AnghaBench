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
struct TYPE_2__ {void* olinfo_status; void* cmd_type_len; int /*<<< orphan*/  buffer_addr; } ;
union ixgbe_adv_tx_desc {TYPE_1__ read; } ;
typedef  int u32 ;
typedef  size_t u16 ;
struct xdp_frame {int len; int /*<<< orphan*/  data; } ;
struct ixgbe_tx_buffer {int bytecount; int gso_segs; union ixgbe_adv_tx_desc* next_to_watch; struct xdp_frame* xdpf; scalar_t__ protocol; } ;
struct ixgbe_ring {size_t next_to_use; size_t count; struct ixgbe_tx_buffer* tx_buffer_info; int /*<<< orphan*/  dev; } ;
struct ixgbe_adapter {struct ixgbe_ring** xdp_ring; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int IXGBE_ADVTXD_DCMD_DEXT ; 
 int IXGBE_ADVTXD_DCMD_IFCS ; 
 int IXGBE_ADVTXD_DTYP_DATA ; 
 int IXGBE_ADVTXD_PAYLEN_SHIFT ; 
 int IXGBE_TXD_CMD ; 
 union ixgbe_adv_tx_desc* IXGBE_TX_DESC (struct ixgbe_ring*,size_t) ; 
 int IXGBE_XDP_CONSUMED ; 
 int IXGBE_XDP_TX ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct ixgbe_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct ixgbe_tx_buffer*,int,int) ; 
 int /*<<< orphan*/  ixgbe_desc_unused (struct ixgbe_ring*) ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ unlikely (int) ; 

int ixgbe_xmit_xdp_ring(struct ixgbe_adapter *adapter,
			struct xdp_frame *xdpf)
{
	struct ixgbe_ring *ring = adapter->xdp_ring[smp_processor_id()];
	struct ixgbe_tx_buffer *tx_buffer;
	union ixgbe_adv_tx_desc *tx_desc;
	u32 len, cmd_type;
	dma_addr_t dma;
	u16 i;

	len = xdpf->len;

	if (unlikely(!ixgbe_desc_unused(ring)))
		return IXGBE_XDP_CONSUMED;

	dma = dma_map_single(ring->dev, xdpf->data, len, DMA_TO_DEVICE);
	if (dma_mapping_error(ring->dev, dma))
		return IXGBE_XDP_CONSUMED;

	/* record the location of the first descriptor for this packet */
	tx_buffer = &ring->tx_buffer_info[ring->next_to_use];
	tx_buffer->bytecount = len;
	tx_buffer->gso_segs = 1;
	tx_buffer->protocol = 0;

	i = ring->next_to_use;
	tx_desc = IXGBE_TX_DESC(ring, i);

	dma_unmap_len_set(tx_buffer, len, len);
	dma_unmap_addr_set(tx_buffer, dma, dma);
	tx_buffer->xdpf = xdpf;

	tx_desc->read.buffer_addr = cpu_to_le64(dma);

	/* put descriptor type bits */
	cmd_type = IXGBE_ADVTXD_DTYP_DATA |
		   IXGBE_ADVTXD_DCMD_DEXT |
		   IXGBE_ADVTXD_DCMD_IFCS;
	cmd_type |= len | IXGBE_TXD_CMD;
	tx_desc->read.cmd_type_len = cpu_to_le32(cmd_type);
	tx_desc->read.olinfo_status =
		cpu_to_le32(len << IXGBE_ADVTXD_PAYLEN_SHIFT);

	/* Avoid any potential race with xdp_xmit and cleanup */
	smp_wmb();

	/* set next_to_watch value indicating a packet is present */
	i++;
	if (i == ring->count)
		i = 0;

	tx_buffer->next_to_watch = tx_desc;
	ring->next_to_use = i;

	return IXGBE_XDP_TX;
}