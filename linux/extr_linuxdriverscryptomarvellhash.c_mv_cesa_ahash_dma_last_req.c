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
struct mv_cesa_tdma_chain {int dummy; } ;
struct mv_cesa_op_ctx {int dummy; } ;
struct mv_cesa_ahash_dma_req {scalar_t__ padding_dma; int /*<<< orphan*/  padding; } ;
struct TYPE_2__ {struct mv_cesa_ahash_dma_req dma; } ;
struct mv_cesa_ahash_req {int /*<<< orphan*/  op_tmpl; int /*<<< orphan*/  len; TYPE_1__ req; } ;
struct mv_cesa_ahash_dma_iter {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_SA_CFG_SRAM_OFFSET ; 
 scalar_t__ CESA_SA_DATA_SRAM_OFFSET ; 
 int /*<<< orphan*/  CESA_SA_DESC_CFG_FRAG_MSK ; 
 int /*<<< orphan*/  CESA_SA_DESC_CFG_LAST_FRAG ; 
 int /*<<< orphan*/  CESA_SA_DESC_CFG_NOT_FRAG ; 
 int /*<<< orphan*/  CESA_SA_DESC_MAC_SRC_TOTAL_LEN_MAX ; 
 scalar_t__ CESA_SA_SRAM_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  CESA_TDMA_DST_IN_SRAM ; 
 int /*<<< orphan*/  CESA_TDMA_SRC_IN_SRAM ; 
 int ENOMEM ; 
 struct mv_cesa_op_ctx* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mv_cesa_op_ctx*) ; 
 unsigned int min (scalar_t__,unsigned int) ; 
 int mv_cesa_ahash_dma_alloc_padding (struct mv_cesa_ahash_dma_req*,int /*<<< orphan*/ ) ; 
 unsigned int mv_cesa_ahash_pad_req (struct mv_cesa_ahash_req*,int /*<<< orphan*/ ) ; 
 int mv_cesa_dma_add_data_transfer (struct mv_cesa_tdma_chain*,scalar_t__,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mv_cesa_op_ctx* mv_cesa_dma_add_frag (struct mv_cesa_tdma_chain*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int mv_cesa_dma_add_result_op (struct mv_cesa_tdma_chain*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mv_cesa_mac_op_is_first_frag (struct mv_cesa_op_ctx*) ; 
 int /*<<< orphan*/  mv_cesa_set_mac_op_total_len (struct mv_cesa_op_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_cesa_update_op_cfg (struct mv_cesa_op_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mv_cesa_op_ctx *
mv_cesa_ahash_dma_last_req(struct mv_cesa_tdma_chain *chain,
			   struct mv_cesa_ahash_dma_iter *dma_iter,
			   struct mv_cesa_ahash_req *creq,
			   unsigned int frag_len, gfp_t flags)
{
	struct mv_cesa_ahash_dma_req *ahashdreq = &creq->req.dma;
	unsigned int len, trailerlen, padoff = 0;
	struct mv_cesa_op_ctx *op;
	int ret;

	/*
	 * If the transfer is smaller than our maximum length, and we have
	 * some data outstanding, we can ask the engine to finish the hash.
	 */
	if (creq->len <= CESA_SA_DESC_MAC_SRC_TOTAL_LEN_MAX && frag_len) {
		op = mv_cesa_dma_add_frag(chain, &creq->op_tmpl, frag_len,
					  flags);
		if (IS_ERR(op))
			return op;

		mv_cesa_set_mac_op_total_len(op, creq->len);
		mv_cesa_update_op_cfg(op, mv_cesa_mac_op_is_first_frag(op) ?
						CESA_SA_DESC_CFG_NOT_FRAG :
						CESA_SA_DESC_CFG_LAST_FRAG,
				      CESA_SA_DESC_CFG_FRAG_MSK);

		ret = mv_cesa_dma_add_result_op(chain,
						CESA_SA_CFG_SRAM_OFFSET,
						CESA_SA_DATA_SRAM_OFFSET,
						CESA_TDMA_SRC_IN_SRAM, flags);
		if (ret)
			return ERR_PTR(-ENOMEM);
		return op;
	}

	/*
	 * The request is longer than the engine can handle, or we have
	 * no data outstanding. Manually generate the padding, adding it
	 * as a "mid" fragment.
	 */
	ret = mv_cesa_ahash_dma_alloc_padding(ahashdreq, flags);
	if (ret)
		return ERR_PTR(ret);

	trailerlen = mv_cesa_ahash_pad_req(creq, ahashdreq->padding);

	len = min(CESA_SA_SRAM_PAYLOAD_SIZE - frag_len, trailerlen);
	if (len) {
		ret = mv_cesa_dma_add_data_transfer(chain,
						CESA_SA_DATA_SRAM_OFFSET +
						frag_len,
						ahashdreq->padding_dma,
						len, CESA_TDMA_DST_IN_SRAM,
						flags);
		if (ret)
			return ERR_PTR(ret);

		op = mv_cesa_dma_add_frag(chain, &creq->op_tmpl, frag_len + len,
					  flags);
		if (IS_ERR(op))
			return op;

		if (len == trailerlen)
			return op;

		padoff += len;
	}

	ret = mv_cesa_dma_add_data_transfer(chain,
					    CESA_SA_DATA_SRAM_OFFSET,
					    ahashdreq->padding_dma +
					    padoff,
					    trailerlen - padoff,
					    CESA_TDMA_DST_IN_SRAM,
					    flags);
	if (ret)
		return ERR_PTR(ret);

	return mv_cesa_dma_add_frag(chain, &creq->op_tmpl, trailerlen - padoff,
				    flags);
}