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
typedef  void u8 ;
typedef  int u32 ;
struct split_key_result {int err; int /*<<< orphan*/  completion; } ;
struct device {int dummy; } ;
struct alginfo {int algtype; int keylen_pad; int /*<<< orphan*/  keylen; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int CAAM_CMD_SZ ; 
 int CAAM_PTR_SZ ; 
 int CLASS_2 ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FIFOLD_TYPE_LAST2 ; 
 int FIFOLD_TYPE_MSG ; 
 int FIFOST_TYPE_SPLIT_KEK ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int KEY_DEST_CLASS_REG ; 
 int LDST_CLASS_2_CCB ; 
 int OP_ALG_AAI_HMAC ; 
 int OP_ALG_ALGSEL_MASK ; 
 int OP_ALG_AS_INIT ; 
 int OP_ALG_DECRYPT ; 
 int OP_TYPE_CLASS2_ALG ; 
 int /*<<< orphan*/  append_fifo_load_as_imm (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_fifo_store (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_key (int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  append_operation (int*,int) ; 
 int caam_jr_enqueue (struct device*,int*,int /*<<< orphan*/ ,struct split_key_result*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_job_desc (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int) ; 
 int /*<<< orphan*/  split_key_done ; 
 int /*<<< orphan*/  split_key_len (int) ; 
 int split_key_pad_len (int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int gen_split_key(struct device *jrdev, u8 *key_out,
		  struct alginfo * const adata, const u8 *key_in, u32 keylen,
		  int max_keylen)
{
	u32 *desc;
	struct split_key_result result;
	dma_addr_t dma_addr_in, dma_addr_out;
	int ret = -ENOMEM;

	adata->keylen = split_key_len(adata->algtype & OP_ALG_ALGSEL_MASK);
	adata->keylen_pad = split_key_pad_len(adata->algtype &
					      OP_ALG_ALGSEL_MASK);

#ifdef DEBUG
	dev_err(jrdev, "split keylen %d split keylen padded %d\n",
		adata->keylen, adata->keylen_pad);
	print_hex_dump(KERN_ERR, "ctx.key@" __stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, key_in, keylen, 1);
#endif

	if (adata->keylen_pad > max_keylen)
		return -EINVAL;

	desc = kmalloc(CAAM_CMD_SZ * 6 + CAAM_PTR_SZ * 2, GFP_KERNEL | GFP_DMA);
	if (!desc) {
		dev_err(jrdev, "unable to allocate key input memory\n");
		return ret;
	}

	dma_addr_in = dma_map_single(jrdev, (void *)key_in, keylen,
				     DMA_TO_DEVICE);
	if (dma_mapping_error(jrdev, dma_addr_in)) {
		dev_err(jrdev, "unable to map key input memory\n");
		goto out_free;
	}

	dma_addr_out = dma_map_single(jrdev, key_out, adata->keylen_pad,
				      DMA_FROM_DEVICE);
	if (dma_mapping_error(jrdev, dma_addr_out)) {
		dev_err(jrdev, "unable to map key output memory\n");
		goto out_unmap_in;
	}

	init_job_desc(desc, 0);
	append_key(desc, dma_addr_in, keylen, CLASS_2 | KEY_DEST_CLASS_REG);

	/* Sets MDHA up into an HMAC-INIT */
	append_operation(desc, (adata->algtype & OP_ALG_ALGSEL_MASK) |
			 OP_ALG_AAI_HMAC | OP_TYPE_CLASS2_ALG | OP_ALG_DECRYPT |
			 OP_ALG_AS_INIT);

	/*
	 * do a FIFO_LOAD of zero, this will trigger the internal key expansion
	 * into both pads inside MDHA
	 */
	append_fifo_load_as_imm(desc, NULL, 0, LDST_CLASS_2_CCB |
				FIFOLD_TYPE_MSG | FIFOLD_TYPE_LAST2);

	/*
	 * FIFO_STORE with the explicit split-key content store
	 * (0x26 output type)
	 */
	append_fifo_store(desc, dma_addr_out, adata->keylen,
			  LDST_CLASS_2_CCB | FIFOST_TYPE_SPLIT_KEK);

#ifdef DEBUG
	print_hex_dump(KERN_ERR, "ctx.key@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, key_in, keylen, 1);
	print_hex_dump(KERN_ERR, "jobdesc@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif

	result.err = 0;
	init_completion(&result.completion);

	ret = caam_jr_enqueue(jrdev, desc, split_key_done, &result);
	if (!ret) {
		/* in progress */
		wait_for_completion(&result.completion);
		ret = result.err;
#ifdef DEBUG
		print_hex_dump(KERN_ERR, "ctx.key@"__stringify(__LINE__)": ",
			       DUMP_PREFIX_ADDRESS, 16, 4, key_out,
			       adata->keylen_pad, 1);
#endif
	}

	dma_unmap_single(jrdev, dma_addr_out, adata->keylen_pad,
			 DMA_FROM_DEVICE);
out_unmap_in:
	dma_unmap_single(jrdev, dma_addr_in, keylen, DMA_TO_DEVICE);
out_free:
	kfree(desc);
	return ret;
}