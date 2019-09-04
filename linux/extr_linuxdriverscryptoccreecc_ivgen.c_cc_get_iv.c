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
struct device {int dummy; } ;
struct cc_ivgen_ctx {unsigned int pool; unsigned int next_iv_ofs; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_drvdata {struct cc_ivgen_ctx* ivgen_handle; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BYPASS ; 
 unsigned int CC_AES_IV_SIZE ; 
 unsigned int CC_IVPOOL_SEQ_LEN ; 
 unsigned int CC_IVPOOL_SIZE ; 
 unsigned int CC_MAX_IVGEN_DMA_ADDRESSES ; 
 unsigned int CTR_RFC3686_IV_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  NS_BIT ; 
 int cc_gen_iv_pool (struct cc_ivgen_ctx*,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_din_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_din_sram (struct cc_hw_desc*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

int cc_get_iv(struct cc_drvdata *drvdata, dma_addr_t iv_out_dma[],
	      unsigned int iv_out_dma_len, unsigned int iv_out_size,
	      struct cc_hw_desc iv_seq[], unsigned int *iv_seq_len)
{
	struct cc_ivgen_ctx *ivgen_ctx = drvdata->ivgen_handle;
	unsigned int idx = *iv_seq_len;
	struct device *dev = drvdata_to_dev(drvdata);
	unsigned int t;

	if (iv_out_size != CC_AES_IV_SIZE &&
	    iv_out_size != CTR_RFC3686_IV_SIZE) {
		return -EINVAL;
	}
	if ((iv_out_dma_len + 1) > CC_IVPOOL_SEQ_LEN) {
		/* The sequence will be longer than allowed */
		return -EINVAL;
	}

	/* check that number of generated IV is limited to max dma address
	 * iv buffer size
	 */
	if (iv_out_dma_len > CC_MAX_IVGEN_DMA_ADDRESSES) {
		/* The sequence will be longer than allowed */
		return -EINVAL;
	}

	for (t = 0; t < iv_out_dma_len; t++) {
		/* Acquire IV from pool */
		hw_desc_init(&iv_seq[idx]);
		set_din_sram(&iv_seq[idx], (ivgen_ctx->pool +
					    ivgen_ctx->next_iv_ofs),
			     iv_out_size);
		set_dout_dlli(&iv_seq[idx], iv_out_dma[t], iv_out_size,
			      NS_BIT, 0);
		set_flow_mode(&iv_seq[idx], BYPASS);
		idx++;
	}

	/* Bypass operation is proceeded by crypto sequence, hence must
	 *  assure bypass-write-transaction by a memory barrier
	 */
	hw_desc_init(&iv_seq[idx]);
	set_din_no_dma(&iv_seq[idx], 0, 0xfffff0);
	set_dout_no_dma(&iv_seq[idx], 0, 0, 1);
	idx++;

	*iv_seq_len = idx; /* update seq length */

	/* Update iv index */
	ivgen_ctx->next_iv_ofs += iv_out_size;

	if ((CC_IVPOOL_SIZE - ivgen_ctx->next_iv_ofs) < CC_AES_IV_SIZE) {
		dev_dbg(dev, "Pool exhausted, regenerating iv-pool\n");
		/* pool is drained -regenerate it! */
		return cc_gen_iv_pool(ivgen_ctx, iv_seq, iv_seq_len);
	}

	return 0;
}