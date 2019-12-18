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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ena_eth_io_tx_desc {int len_ctrl; int buff_addr_hi_hdr_sz; int meta_ctrl; scalar_t__ buff_addr_lo; } ;
struct ena_com_tx_ctx {int header_len; int num_bufs; int req_id; int df; int tso_enable; int l3_proto; int l4_proto; int l3_csum_enable; int l4_csum_enable; int l4_csum_partial; scalar_t__ meta_valid; void* push_header; struct ena_com_buf* ena_bufs; } ;
struct ena_com_io_sq {int tail; scalar_t__ direction; int tx_max_header_size; scalar_t__ mem_queue_type; int phase; scalar_t__ dma_addr_bits; } ;
struct ena_com_buf {int len; int paddr; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_DEV ; 
 scalar_t__ ENA_COM_IO_QUEUE_DIRECTION_TX ; 
 int ENA_ETH_IO_TX_DESC_ADDR_HI_MASK ; 
 int ENA_ETH_IO_TX_DESC_COMP_REQ_MASK ; 
 int ENA_ETH_IO_TX_DESC_DF_MASK ; 
 int ENA_ETH_IO_TX_DESC_DF_SHIFT ; 
 int ENA_ETH_IO_TX_DESC_FIRST_MASK ; 
 int ENA_ETH_IO_TX_DESC_HEADER_LENGTH_MASK ; 
 int ENA_ETH_IO_TX_DESC_HEADER_LENGTH_SHIFT ; 
 int ENA_ETH_IO_TX_DESC_L3_CSUM_EN_MASK ; 
 int ENA_ETH_IO_TX_DESC_L3_CSUM_EN_SHIFT ; 
 int ENA_ETH_IO_TX_DESC_L3_PROTO_IDX_MASK ; 
 int ENA_ETH_IO_TX_DESC_L4_CSUM_EN_MASK ; 
 int ENA_ETH_IO_TX_DESC_L4_CSUM_EN_SHIFT ; 
 int ENA_ETH_IO_TX_DESC_L4_CSUM_PARTIAL_MASK ; 
 int ENA_ETH_IO_TX_DESC_L4_CSUM_PARTIAL_SHIFT ; 
 int ENA_ETH_IO_TX_DESC_L4_PROTO_IDX_MASK ; 
 int ENA_ETH_IO_TX_DESC_L4_PROTO_IDX_SHIFT ; 
 int ENA_ETH_IO_TX_DESC_LAST_MASK ; 
 int ENA_ETH_IO_TX_DESC_LENGTH_MASK ; 
 int ENA_ETH_IO_TX_DESC_PHASE_MASK ; 
 int ENA_ETH_IO_TX_DESC_PHASE_SHIFT ; 
 int ENA_ETH_IO_TX_DESC_REQ_ID_HI_MASK ; 
 int ENA_ETH_IO_TX_DESC_REQ_ID_HI_SHIFT ; 
 int ENA_ETH_IO_TX_DESC_REQ_ID_LO_MASK ; 
 int ENA_ETH_IO_TX_DESC_REQ_ID_LO_SHIFT ; 
 int ENA_ETH_IO_TX_DESC_TSO_EN_MASK ; 
 int ENA_ETH_IO_TX_DESC_TSO_EN_SHIFT ; 
 int ENOMEM ; 
 int GENMASK_ULL (scalar_t__,int) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int ena_com_close_bounce_buffer (struct ena_com_io_sq*) ; 
 int ena_com_create_and_store_tx_meta_desc (struct ena_com_io_sq*,struct ena_com_tx_ctx*) ; 
 scalar_t__ ena_com_meta_desc_changed (struct ena_com_io_sq*,struct ena_com_tx_ctx*) ; 
 int /*<<< orphan*/  ena_com_sq_have_enough_space (struct ena_com_io_sq*,int) ; 
 int ena_com_sq_update_tail (struct ena_com_io_sq*) ; 
 int ena_com_write_header_to_bounce (struct ena_com_io_sq*,void*,int) ; 
 struct ena_eth_io_tx_desc* get_sq_desc (struct ena_com_io_sq*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct ena_eth_io_tx_desc*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 scalar_t__ unlikely (int) ; 

int ena_com_prepare_tx(struct ena_com_io_sq *io_sq,
		       struct ena_com_tx_ctx *ena_tx_ctx,
		       int *nb_hw_desc)
{
	struct ena_eth_io_tx_desc *desc = NULL;
	struct ena_com_buf *ena_bufs = ena_tx_ctx->ena_bufs;
	void *buffer_to_push = ena_tx_ctx->push_header;
	u16 header_len = ena_tx_ctx->header_len;
	u16 num_bufs = ena_tx_ctx->num_bufs;
	u16 start_tail = io_sq->tail;
	int i, rc;
	bool have_meta;
	u64 addr_hi;

	WARN(io_sq->direction != ENA_COM_IO_QUEUE_DIRECTION_TX, "wrong Q type");

	/* num_bufs +1 for potential meta desc */
	if (unlikely(!ena_com_sq_have_enough_space(io_sq, num_bufs + 1))) {
		pr_debug("Not enough space in the tx queue\n");
		return -ENOMEM;
	}

	if (unlikely(header_len > io_sq->tx_max_header_size)) {
		pr_err("header size is too large %d max header: %d\n",
		       header_len, io_sq->tx_max_header_size);
		return -EINVAL;
	}

	if (unlikely(io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV &&
		     !buffer_to_push))
		return -EINVAL;

	rc = ena_com_write_header_to_bounce(io_sq, buffer_to_push, header_len);
	if (unlikely(rc))
		return rc;

	have_meta = ena_tx_ctx->meta_valid && ena_com_meta_desc_changed(io_sq,
			ena_tx_ctx);
	if (have_meta) {
		rc = ena_com_create_and_store_tx_meta_desc(io_sq, ena_tx_ctx);
		if (unlikely(rc))
			return rc;
	}

	/* If the caller doesn't want to send packets */
	if (unlikely(!num_bufs && !header_len)) {
		rc = ena_com_close_bounce_buffer(io_sq);
		*nb_hw_desc = io_sq->tail - start_tail;
		return rc;
	}

	desc = get_sq_desc(io_sq);
	if (unlikely(!desc))
		return -EFAULT;
	memset(desc, 0x0, sizeof(struct ena_eth_io_tx_desc));

	/* Set first desc when we don't have meta descriptor */
	if (!have_meta)
		desc->len_ctrl |= ENA_ETH_IO_TX_DESC_FIRST_MASK;

	desc->buff_addr_hi_hdr_sz |= (header_len <<
		ENA_ETH_IO_TX_DESC_HEADER_LENGTH_SHIFT) &
		ENA_ETH_IO_TX_DESC_HEADER_LENGTH_MASK;
	desc->len_ctrl |= (io_sq->phase << ENA_ETH_IO_TX_DESC_PHASE_SHIFT) &
		ENA_ETH_IO_TX_DESC_PHASE_MASK;

	desc->len_ctrl |= ENA_ETH_IO_TX_DESC_COMP_REQ_MASK;

	/* Bits 0-9 */
	desc->meta_ctrl |= (ena_tx_ctx->req_id <<
		ENA_ETH_IO_TX_DESC_REQ_ID_LO_SHIFT) &
		ENA_ETH_IO_TX_DESC_REQ_ID_LO_MASK;

	desc->meta_ctrl |= (ena_tx_ctx->df <<
		ENA_ETH_IO_TX_DESC_DF_SHIFT) &
		ENA_ETH_IO_TX_DESC_DF_MASK;

	/* Bits 10-15 */
	desc->len_ctrl |= ((ena_tx_ctx->req_id >> 10) <<
		ENA_ETH_IO_TX_DESC_REQ_ID_HI_SHIFT) &
		ENA_ETH_IO_TX_DESC_REQ_ID_HI_MASK;

	if (ena_tx_ctx->meta_valid) {
		desc->meta_ctrl |= (ena_tx_ctx->tso_enable <<
			ENA_ETH_IO_TX_DESC_TSO_EN_SHIFT) &
			ENA_ETH_IO_TX_DESC_TSO_EN_MASK;
		desc->meta_ctrl |= ena_tx_ctx->l3_proto &
			ENA_ETH_IO_TX_DESC_L3_PROTO_IDX_MASK;
		desc->meta_ctrl |= (ena_tx_ctx->l4_proto <<
			ENA_ETH_IO_TX_DESC_L4_PROTO_IDX_SHIFT) &
			ENA_ETH_IO_TX_DESC_L4_PROTO_IDX_MASK;
		desc->meta_ctrl |= (ena_tx_ctx->l3_csum_enable <<
			ENA_ETH_IO_TX_DESC_L3_CSUM_EN_SHIFT) &
			ENA_ETH_IO_TX_DESC_L3_CSUM_EN_MASK;
		desc->meta_ctrl |= (ena_tx_ctx->l4_csum_enable <<
			ENA_ETH_IO_TX_DESC_L4_CSUM_EN_SHIFT) &
			ENA_ETH_IO_TX_DESC_L4_CSUM_EN_MASK;
		desc->meta_ctrl |= (ena_tx_ctx->l4_csum_partial <<
			ENA_ETH_IO_TX_DESC_L4_CSUM_PARTIAL_SHIFT) &
			ENA_ETH_IO_TX_DESC_L4_CSUM_PARTIAL_MASK;
	}

	for (i = 0; i < num_bufs; i++) {
		/* The first desc share the same desc as the header */
		if (likely(i != 0)) {
			rc = ena_com_sq_update_tail(io_sq);
			if (unlikely(rc))
				return rc;

			desc = get_sq_desc(io_sq);
			if (unlikely(!desc))
				return -EFAULT;

			memset(desc, 0x0, sizeof(struct ena_eth_io_tx_desc));

			desc->len_ctrl |= (io_sq->phase <<
				ENA_ETH_IO_TX_DESC_PHASE_SHIFT) &
				ENA_ETH_IO_TX_DESC_PHASE_MASK;
		}

		desc->len_ctrl |= ena_bufs->len &
			ENA_ETH_IO_TX_DESC_LENGTH_MASK;

		addr_hi = ((ena_bufs->paddr &
			GENMASK_ULL(io_sq->dma_addr_bits - 1, 32)) >> 32);

		desc->buff_addr_lo = (u32)ena_bufs->paddr;
		desc->buff_addr_hi_hdr_sz |= addr_hi &
			ENA_ETH_IO_TX_DESC_ADDR_HI_MASK;
		ena_bufs++;
	}

	/* set the last desc indicator */
	desc->len_ctrl |= ENA_ETH_IO_TX_DESC_LAST_MASK;

	rc = ena_com_sq_update_tail(io_sq);
	if (unlikely(rc))
		return rc;

	rc = ena_com_close_bounce_buffer(io_sq);

	*nb_hw_desc = io_sq->tail - start_tail;
	return rc;
}