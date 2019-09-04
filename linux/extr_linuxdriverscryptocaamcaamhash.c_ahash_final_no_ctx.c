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
struct device {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct caam_hash_state {int /*<<< orphan*/  buf_dma; } ;
struct caam_hash_ctx {int /*<<< orphan*/  sh_desc_digest_dma; int /*<<< orphan*/  sh_desc_digest; struct device* jrdev; } ;
struct TYPE_2__ {int flags; } ;
struct ahash_request {TYPE_1__ base; } ;
struct ahash_edesc {int /*<<< orphan*/ * hw_desc; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ahash_done ; 
 struct ahash_edesc* ahash_edesc_alloc (struct caam_hash_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct caam_hash_state* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_unmap (struct device*,struct ahash_edesc*,struct ahash_request*,int) ; 
 int /*<<< orphan*/  ahash_unmap_ctx (struct device*,struct ahash_edesc*,struct ahash_request*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_seq_in_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int caam_jr_enqueue (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ahash_request*) ; 
 struct caam_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/ * current_buf (struct caam_hash_state*) ; 
 int* current_buflen (struct caam_hash_state*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ahash_edesc*) ; 
 int map_seq_out_ptr_ctx (int /*<<< orphan*/ *,struct device*,struct caam_hash_state*,int) ; 

__attribute__((used)) static int ahash_final_no_ctx(struct ahash_request *req)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	struct caam_hash_state *state = ahash_request_ctx(req);
	struct device *jrdev = ctx->jrdev;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	u8 *buf = current_buf(state);
	int buflen = *current_buflen(state);
	u32 *desc;
	int digestsize = crypto_ahash_digestsize(ahash);
	struct ahash_edesc *edesc;
	int ret;

	/* allocate space for base edesc and hw desc commands, link tables */
	edesc = ahash_edesc_alloc(ctx, 0, ctx->sh_desc_digest,
				  ctx->sh_desc_digest_dma, flags);
	if (!edesc)
		return -ENOMEM;

	desc = edesc->hw_desc;

	if (buflen) {
		state->buf_dma = dma_map_single(jrdev, buf, buflen,
						DMA_TO_DEVICE);
		if (dma_mapping_error(jrdev, state->buf_dma)) {
			dev_err(jrdev, "unable to map src\n");
			goto unmap;
		}

		append_seq_in_ptr(desc, state->buf_dma, buflen, 0);
	}

	ret = map_seq_out_ptr_ctx(desc, jrdev, state, digestsize);
	if (ret)
		goto unmap;

#ifdef DEBUG
	print_hex_dump(KERN_ERR, "jobdesc@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc), 1);
#endif

	ret = caam_jr_enqueue(jrdev, desc, ahash_done, req);
	if (!ret) {
		ret = -EINPROGRESS;
	} else {
		ahash_unmap_ctx(jrdev, edesc, req, digestsize, DMA_FROM_DEVICE);
		kfree(edesc);
	}

	return ret;
 unmap:
	ahash_unmap(jrdev, edesc, req, digestsize);
	kfree(edesc);
	return -ENOMEM;

}