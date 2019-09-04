#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct i40e_vsi {TYPE_1__* back; } ;
struct i40e_tx_desc {int cmd_type_offset_bsz; scalar_t__ buffer_addr; } ;
struct i40e_tx_buffer {int tx_flags; struct i40e_tx_desc* next_to_watch; int /*<<< orphan*/ * raw_buf; } ;
struct i40e_ring {size_t next_to_clean; TYPE_2__* q_vector; scalar_t__ count; struct i40e_tx_buffer* tx_bi; int /*<<< orphan*/  dev; struct i40e_vsi* vsi; } ;
struct TYPE_4__ {int /*<<< orphan*/  v_idx; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int I40E_FLAG_MSIX_ENABLED ; 
 struct i40e_tx_desc* I40E_TX_DESC (struct i40e_ring*,size_t) ; 
 int /*<<< orphan*/  I40E_TX_DESC_DTYPE_DESC_DONE ; 
 int I40E_TX_FLAGS_FD_SB ; 
 int cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct i40e_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct i40e_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct i40e_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_irq_dynamic_enable (struct i40e_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool i40e_clean_fdir_tx_irq(struct i40e_ring *tx_ring, int budget)
{
	struct i40e_vsi *vsi = tx_ring->vsi;
	u16 i = tx_ring->next_to_clean;
	struct i40e_tx_buffer *tx_buf;
	struct i40e_tx_desc *tx_desc;

	tx_buf = &tx_ring->tx_bi[i];
	tx_desc = I40E_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	do {
		struct i40e_tx_desc *eop_desc = tx_buf->next_to_watch;

		/* if next_to_watch is not set then there is no work pending */
		if (!eop_desc)
			break;

		/* prevent any other reads prior to eop_desc */
		smp_rmb();

		/* if the descriptor isn't done, no work yet to do */
		if (!(eop_desc->cmd_type_offset_bsz &
		      cpu_to_le64(I40E_TX_DESC_DTYPE_DESC_DONE)))
			break;

		/* clear next_to_watch to prevent false hangs */
		tx_buf->next_to_watch = NULL;

		tx_desc->buffer_addr = 0;
		tx_desc->cmd_type_offset_bsz = 0;
		/* move past filter desc */
		tx_buf++;
		tx_desc++;
		i++;
		if (unlikely(!i)) {
			i -= tx_ring->count;
			tx_buf = tx_ring->tx_bi;
			tx_desc = I40E_TX_DESC(tx_ring, 0);
		}
		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buf, dma),
				 dma_unmap_len(tx_buf, len),
				 DMA_TO_DEVICE);
		if (tx_buf->tx_flags & I40E_TX_FLAGS_FD_SB)
			kfree(tx_buf->raw_buf);

		tx_buf->raw_buf = NULL;
		tx_buf->tx_flags = 0;
		tx_buf->next_to_watch = NULL;
		dma_unmap_len_set(tx_buf, len, 0);
		tx_desc->buffer_addr = 0;
		tx_desc->cmd_type_offset_bsz = 0;

		/* move us past the eop_desc for start of next FD desc */
		tx_buf++;
		tx_desc++;
		i++;
		if (unlikely(!i)) {
			i -= tx_ring->count;
			tx_buf = tx_ring->tx_bi;
			tx_desc = I40E_TX_DESC(tx_ring, 0);
		}

		/* update budget accounting */
		budget--;
	} while (likely(budget));

	i += tx_ring->count;
	tx_ring->next_to_clean = i;

	if (vsi->back->flags & I40E_FLAG_MSIX_ENABLED)
		i40e_irq_dynamic_enable(vsi, tx_ring->q_vector->v_idx);

	return budget > 0;
}