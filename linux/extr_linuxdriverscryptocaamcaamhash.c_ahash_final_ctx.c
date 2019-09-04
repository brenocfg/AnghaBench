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
struct sec4_sg_entry {int dummy; } ;
struct device {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct caam_hash_state {int /*<<< orphan*/  ctx_dma; } ;
struct caam_hash_ctx {scalar_t__ ctx_len; int /*<<< orphan*/  sh_desc_fin_dma; int /*<<< orphan*/  sh_desc_fin; struct device* jrdev; } ;
struct TYPE_2__ {int flags; } ;
struct ahash_request {TYPE_1__ base; } ;
struct ahash_edesc {int sec4_sg_bytes; int /*<<< orphan*/  sec4_sg_dma; scalar_t__ sec4_sg; int /*<<< orphan*/ * hw_desc; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LDST_SGF ; 
 int /*<<< orphan*/  ahash_done_ctx_src ; 
 struct ahash_edesc* ahash_edesc_alloc (struct caam_hash_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct caam_hash_state* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_unmap_ctx (struct device*,struct ahash_edesc*,struct ahash_request*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_seq_in_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_seq_out_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int buf_map_to_sec4_sg (struct device*,scalar_t__,struct caam_hash_state*) ; 
 int caam_jr_enqueue (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ahash_request*) ; 
 struct caam_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int ctx_map_to_sec4_sg (struct device*,struct caam_hash_state*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int* current_buflen (struct caam_hash_state*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ahash_edesc*) ; 
 int /*<<< orphan*/  sg_to_sec4_set_last (scalar_t__) ; 

__attribute__((used)) static int ahash_final_ctx(struct ahash_request *req)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	struct caam_hash_state *state = ahash_request_ctx(req);
	struct device *jrdev = ctx->jrdev;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	int buflen = *current_buflen(state);
	u32 *desc;
	int sec4_sg_bytes, sec4_sg_src_index;
	int digestsize = crypto_ahash_digestsize(ahash);
	struct ahash_edesc *edesc;
	int ret;

	sec4_sg_src_index = 1 + (buflen ? 1 : 0);
	sec4_sg_bytes = sec4_sg_src_index * sizeof(struct sec4_sg_entry);

	/* allocate space for base edesc and hw desc commands, link tables */
	edesc = ahash_edesc_alloc(ctx, sec4_sg_src_index,
				  ctx->sh_desc_fin, ctx->sh_desc_fin_dma,
				  flags);
	if (!edesc)
		return -ENOMEM;

	desc = edesc->hw_desc;

	edesc->sec4_sg_bytes = sec4_sg_bytes;

	ret = ctx_map_to_sec4_sg(jrdev, state, ctx->ctx_len,
				 edesc->sec4_sg, DMA_BIDIRECTIONAL);
	if (ret)
		goto unmap_ctx;

	ret = buf_map_to_sec4_sg(jrdev, edesc->sec4_sg + 1, state);
	if (ret)
		goto unmap_ctx;

	sg_to_sec4_set_last(edesc->sec4_sg + sec4_sg_src_index - 1);

	edesc->sec4_sg_dma = dma_map_single(jrdev, edesc->sec4_sg,
					    sec4_sg_bytes, DMA_TO_DEVICE);
	if (dma_mapping_error(jrdev, edesc->sec4_sg_dma)) {
		dev_err(jrdev, "unable to map S/G table\n");
		ret = -ENOMEM;
		goto unmap_ctx;
	}

	append_seq_in_ptr(desc, edesc->sec4_sg_dma, ctx->ctx_len + buflen,
			  LDST_SGF);
	append_seq_out_ptr(desc, state->ctx_dma, digestsize, 0);

#ifdef DEBUG
	print_hex_dump(KERN_ERR, "jobdesc@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif

	ret = caam_jr_enqueue(jrdev, desc, ahash_done_ctx_src, req);
	if (ret)
		goto unmap_ctx;

	return -EINPROGRESS;
 unmap_ctx:
	ahash_unmap_ctx(jrdev, edesc, req, digestsize, DMA_BIDIRECTIONAL);
	kfree(edesc);
	return ret;
}