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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct split_key_result {int err; int /*<<< orphan*/  completion; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int algtype; } ;
struct caam_hash_ctx {TYPE_1__ adata; struct device* jrdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int CAAM_CMD_SZ ; 
 int CAAM_PTR_SZ ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int FIFOLD_CLASS_CLASS2 ; 
 int FIFOLD_TYPE_LAST2 ; 
 int FIFOLD_TYPE_MSG ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int LDST_CLASS_2_CCB ; 
 int LDST_SRCDST_BYTE_CONTEXT ; 
 int OP_ALG_AS_INITFINAL ; 
 int OP_ALG_ENCRYPT ; 
 int /*<<< orphan*/  append_operation (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  append_seq_fifo_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  append_seq_in_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_seq_out_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_seq_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int caam_jr_enqueue (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct split_key_result*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_job_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int) ; 
 int /*<<< orphan*/  split_key_done ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hash_digest_key(struct caam_hash_ctx *ctx, const u8 *key_in,
			   u32 *keylen, u8 *key_out, u32 digestsize)
{
	struct device *jrdev = ctx->jrdev;
	u32 *desc;
	struct split_key_result result;
	dma_addr_t src_dma, dst_dma;
	int ret;

	desc = kmalloc(CAAM_CMD_SZ * 8 + CAAM_PTR_SZ * 2, GFP_KERNEL | GFP_DMA);
	if (!desc) {
		dev_err(jrdev, "unable to allocate key input memory\n");
		return -ENOMEM;
	}

	init_job_desc(desc, 0);

	src_dma = dma_map_single(jrdev, (void *)key_in, *keylen,
				 DMA_TO_DEVICE);
	if (dma_mapping_error(jrdev, src_dma)) {
		dev_err(jrdev, "unable to map key input memory\n");
		kfree(desc);
		return -ENOMEM;
	}
	dst_dma = dma_map_single(jrdev, (void *)key_out, digestsize,
				 DMA_FROM_DEVICE);
	if (dma_mapping_error(jrdev, dst_dma)) {
		dev_err(jrdev, "unable to map key output memory\n");
		dma_unmap_single(jrdev, src_dma, *keylen, DMA_TO_DEVICE);
		kfree(desc);
		return -ENOMEM;
	}

	/* Job descriptor to perform unkeyed hash on key_in */
	append_operation(desc, ctx->adata.algtype | OP_ALG_ENCRYPT |
			 OP_ALG_AS_INITFINAL);
	append_seq_in_ptr(desc, src_dma, *keylen, 0);
	append_seq_fifo_load(desc, *keylen, FIFOLD_CLASS_CLASS2 |
			     FIFOLD_TYPE_LAST2 | FIFOLD_TYPE_MSG);
	append_seq_out_ptr(desc, dst_dma, digestsize, 0);
	append_seq_store(desc, digestsize, LDST_CLASS_2_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

#ifdef DEBUG
	print_hex_dump(KERN_ERR, "key_in@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, key_in, *keylen, 1);
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
		print_hex_dump(KERN_ERR,
			       "digested key@"__stringify(__LINE__)": ",
			       DUMP_PREFIX_ADDRESS, 16, 4, key_in,
			       digestsize, 1);
#endif
	}
	dma_unmap_single(jrdev, src_dma, *keylen, DMA_TO_DEVICE);
	dma_unmap_single(jrdev, dst_dma, digestsize, DMA_FROM_DEVICE);

	*keylen = digestsize;

	kfree(desc);

	return ret;
}