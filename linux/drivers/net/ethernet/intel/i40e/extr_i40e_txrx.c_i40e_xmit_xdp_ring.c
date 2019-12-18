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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct xdp_frame {int /*<<< orphan*/  len; void* data; } ;
struct i40e_tx_desc {int /*<<< orphan*/  cmd_type_offset_bsz; int /*<<< orphan*/  buffer_addr; } ;
struct i40e_tx_buffer {int gso_segs; struct i40e_tx_desc* next_to_watch; struct xdp_frame* xdpf; int /*<<< orphan*/  bytecount; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_busy; } ;
struct i40e_ring {size_t next_to_use; size_t count; struct i40e_tx_buffer* tx_bi; int /*<<< orphan*/  dev; TYPE_1__ tx_stats; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  I40E_DESC_UNUSED (struct i40e_ring*) ; 
 int I40E_TXD_CMD ; 
 struct i40e_tx_desc* I40E_TX_DESC (struct i40e_ring*,size_t) ; 
 int I40E_TX_DESC_CMD_ICRC ; 
 int I40E_XDP_CONSUMED ; 
 int I40E_XDP_TX ; 
 int /*<<< orphan*/  build_ctob (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct i40e_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct i40e_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_xmit_xdp_ring(struct xdp_frame *xdpf,
			      struct i40e_ring *xdp_ring)
{
	u16 i = xdp_ring->next_to_use;
	struct i40e_tx_buffer *tx_bi;
	struct i40e_tx_desc *tx_desc;
	void *data = xdpf->data;
	u32 size = xdpf->len;
	dma_addr_t dma;

	if (!unlikely(I40E_DESC_UNUSED(xdp_ring))) {
		xdp_ring->tx_stats.tx_busy++;
		return I40E_XDP_CONSUMED;
	}
	dma = dma_map_single(xdp_ring->dev, data, size, DMA_TO_DEVICE);
	if (dma_mapping_error(xdp_ring->dev, dma))
		return I40E_XDP_CONSUMED;

	tx_bi = &xdp_ring->tx_bi[i];
	tx_bi->bytecount = size;
	tx_bi->gso_segs = 1;
	tx_bi->xdpf = xdpf;

	/* record length, and DMA address */
	dma_unmap_len_set(tx_bi, len, size);
	dma_unmap_addr_set(tx_bi, dma, dma);

	tx_desc = I40E_TX_DESC(xdp_ring, i);
	tx_desc->buffer_addr = cpu_to_le64(dma);
	tx_desc->cmd_type_offset_bsz = build_ctob(I40E_TX_DESC_CMD_ICRC
						  | I40E_TXD_CMD,
						  0, size, 0);

	/* Make certain all of the status bits have been updated
	 * before next_to_watch is written.
	 */
	smp_wmb();

	i++;
	if (i == xdp_ring->count)
		i = 0;

	tx_bi->next_to_watch = tx_desc;
	xdp_ring->next_to_use = i;

	return I40E_XDP_TX;
}