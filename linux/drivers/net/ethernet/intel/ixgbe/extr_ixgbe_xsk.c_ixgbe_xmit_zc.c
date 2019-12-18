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
struct xdp_desc {int len; int /*<<< orphan*/  addr; } ;
struct ixgbe_tx_buffer {int bytecount; int gso_segs; int /*<<< orphan*/ * xdpf; } ;
struct ixgbe_ring {size_t next_to_use; size_t count; int /*<<< orphan*/  xsk_umem; struct ixgbe_tx_buffer* tx_buffer_info; int /*<<< orphan*/  dev; int /*<<< orphan*/  netdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int IXGBE_ADVTXD_DCMD_DEXT ; 
 int IXGBE_ADVTXD_DCMD_IFCS ; 
 int IXGBE_ADVTXD_DTYP_DATA ; 
 int IXGBE_ADVTXD_PAYLEN_SHIFT ; 
 int IXGBE_TXD_CMD ; 
 union ixgbe_adv_tx_desc* IXGBE_TX_DESC (struct ixgbe_ring*,size_t) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_desc_unused (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_xdp_ring_update_tail (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_umem_get_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_umem_consume_tx (int /*<<< orphan*/ ,struct xdp_desc*) ; 
 int /*<<< orphan*/  xsk_umem_consume_tx_done (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ixgbe_xmit_zc(struct ixgbe_ring *xdp_ring, unsigned int budget)
{
	union ixgbe_adv_tx_desc *tx_desc = NULL;
	struct ixgbe_tx_buffer *tx_bi;
	bool work_done = true;
	struct xdp_desc desc;
	dma_addr_t dma;
	u32 cmd_type;

	while (budget-- > 0) {
		if (unlikely(!ixgbe_desc_unused(xdp_ring)) ||
		    !netif_carrier_ok(xdp_ring->netdev)) {
			work_done = false;
			break;
		}

		if (!xsk_umem_consume_tx(xdp_ring->xsk_umem, &desc))
			break;

		dma = xdp_umem_get_dma(xdp_ring->xsk_umem, desc.addr);

		dma_sync_single_for_device(xdp_ring->dev, dma, desc.len,
					   DMA_BIDIRECTIONAL);

		tx_bi = &xdp_ring->tx_buffer_info[xdp_ring->next_to_use];
		tx_bi->bytecount = desc.len;
		tx_bi->xdpf = NULL;
		tx_bi->gso_segs = 1;

		tx_desc = IXGBE_TX_DESC(xdp_ring, xdp_ring->next_to_use);
		tx_desc->read.buffer_addr = cpu_to_le64(dma);

		/* put descriptor type bits */
		cmd_type = IXGBE_ADVTXD_DTYP_DATA |
			   IXGBE_ADVTXD_DCMD_DEXT |
			   IXGBE_ADVTXD_DCMD_IFCS;
		cmd_type |= desc.len | IXGBE_TXD_CMD;
		tx_desc->read.cmd_type_len = cpu_to_le32(cmd_type);
		tx_desc->read.olinfo_status =
			cpu_to_le32(desc.len << IXGBE_ADVTXD_PAYLEN_SHIFT);

		xdp_ring->next_to_use++;
		if (xdp_ring->next_to_use == xdp_ring->count)
			xdp_ring->next_to_use = 0;
	}

	if (tx_desc) {
		ixgbe_xdp_ring_update_tail(xdp_ring);
		xsk_umem_consume_tx_done(xdp_ring->xsk_umem);
	}

	return !!budget && work_done;
}