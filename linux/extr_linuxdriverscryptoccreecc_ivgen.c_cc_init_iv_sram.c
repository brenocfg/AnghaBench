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
struct cc_ivgen_ctx {scalar_t__ pool; int /*<<< orphan*/  pool_meta_dma; scalar_t__ ctr_iv; scalar_t__ ctr_key; int /*<<< orphan*/  pool_meta; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_drvdata {struct cc_ivgen_ctx* ivgen_handle; } ;

/* Variables and functions */
 scalar_t__ AES_KEYSIZE_128 ; 
 int /*<<< orphan*/  BYPASS ; 
 int /*<<< orphan*/  CC_IVPOOL_META_SIZE ; 
 int CC_IVPOOL_SEQ_LEN ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  NS_BIT ; 
 int cc_gen_iv_pool (struct cc_ivgen_ctx*,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int send_request_init (struct cc_drvdata*,struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_sram (struct cc_hw_desc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

int cc_init_iv_sram(struct cc_drvdata *drvdata)
{
	struct cc_ivgen_ctx *ivgen_ctx = drvdata->ivgen_handle;
	struct cc_hw_desc iv_seq[CC_IVPOOL_SEQ_LEN];
	unsigned int iv_seq_len = 0;
	int rc;

	/* Generate initial enc. key/iv */
	get_random_bytes(ivgen_ctx->pool_meta, CC_IVPOOL_META_SIZE);

	/* The first 32B reserved for the enc. Key/IV */
	ivgen_ctx->ctr_key = ivgen_ctx->pool;
	ivgen_ctx->ctr_iv = ivgen_ctx->pool + AES_KEYSIZE_128;

	/* Copy initial enc. key and IV to SRAM at a single descriptor */
	hw_desc_init(&iv_seq[iv_seq_len]);
	set_din_type(&iv_seq[iv_seq_len], DMA_DLLI, ivgen_ctx->pool_meta_dma,
		     CC_IVPOOL_META_SIZE, NS_BIT);
	set_dout_sram(&iv_seq[iv_seq_len], ivgen_ctx->pool,
		      CC_IVPOOL_META_SIZE);
	set_flow_mode(&iv_seq[iv_seq_len], BYPASS);
	iv_seq_len++;

	/* Generate initial pool */
	rc = cc_gen_iv_pool(ivgen_ctx, iv_seq, &iv_seq_len);
	if (rc)
		return rc;

	/* Fire-and-forget */
	return send_request_init(drvdata, iv_seq, iv_seq_len);
}