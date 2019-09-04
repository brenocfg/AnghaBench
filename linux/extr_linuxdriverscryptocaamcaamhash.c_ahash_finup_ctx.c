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
struct device {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct caam_hash_state {int /*<<< orphan*/  ctx_dma; } ;
struct caam_hash_ctx {scalar_t__ ctx_len; int /*<<< orphan*/  sh_desc_fin_dma; int /*<<< orphan*/  sh_desc_fin; struct device* jrdev; } ;
struct TYPE_2__ {int flags; } ;
struct ahash_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct ahash_edesc {int src_nents; scalar_t__ sec4_sg; int /*<<< orphan*/ * hw_desc; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ahash_done_ctx_src ; 
 int ahash_edesc_add_src (struct caam_hash_ctx*,struct ahash_edesc*,struct ahash_request*,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ahash_edesc* ahash_edesc_alloc (struct caam_hash_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct caam_hash_state* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_unmap_ctx (struct device*,struct ahash_edesc*,struct ahash_request*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_seq_out_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int buf_map_to_sec4_sg (struct device*,scalar_t__,struct caam_hash_state*) ; 
 int caam_jr_enqueue (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ahash_request*) ; 
 struct caam_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int ctx_map_to_sec4_sg (struct device*,struct caam_hash_state*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int* current_buflen (struct caam_hash_state*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dma_map_sg (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ahash_edesc*) ; 
 int sg_nents_for_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahash_finup_ctx(struct ahash_request *req)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	struct caam_hash_state *state = ahash_request_ctx(req);
	struct device *jrdev = ctx->jrdev;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	int buflen = *current_buflen(state);
	u32 *desc;
	int sec4_sg_src_index;
	int src_nents, mapped_nents;
	int digestsize = crypto_ahash_digestsize(ahash);
	struct ahash_edesc *edesc;
	int ret;

	src_nents = sg_nents_for_len(req->src, req->nbytes);
	if (src_nents < 0) {
		dev_err(jrdev, "Invalid number of src SG.\n");
		return src_nents;
	}

	if (src_nents) {
		mapped_nents = dma_map_sg(jrdev, req->src, src_nents,
					  DMA_TO_DEVICE);
		if (!mapped_nents) {
			dev_err(jrdev, "unable to DMA map source\n");
			return -ENOMEM;
		}
	} else {
		mapped_nents = 0;
	}

	sec4_sg_src_index = 1 + (buflen ? 1 : 0);

	/* allocate space for base edesc and hw desc commands, link tables */
	edesc = ahash_edesc_alloc(ctx, sec4_sg_src_index + mapped_nents,
				  ctx->sh_desc_fin, ctx->sh_desc_fin_dma,
				  flags);
	if (!edesc) {
		dma_unmap_sg(jrdev, req->src, src_nents, DMA_TO_DEVICE);
		return -ENOMEM;
	}

	desc = edesc->hw_desc;

	edesc->src_nents = src_nents;

	ret = ctx_map_to_sec4_sg(jrdev, state, ctx->ctx_len,
				 edesc->sec4_sg, DMA_BIDIRECTIONAL);
	if (ret)
		goto unmap_ctx;

	ret = buf_map_to_sec4_sg(jrdev, edesc->sec4_sg + 1, state);
	if (ret)
		goto unmap_ctx;

	ret = ahash_edesc_add_src(ctx, edesc, req, mapped_nents,
				  sec4_sg_src_index, ctx->ctx_len + buflen,
				  req->nbytes);
	if (ret)
		goto unmap_ctx;

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