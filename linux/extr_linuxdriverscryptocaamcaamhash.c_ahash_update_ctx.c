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
struct sec4_sg_entry {int dummy; } ;
struct device {int dummy; } ;
struct crypto_ahash {int /*<<< orphan*/  base; } ;
struct caam_hash_state {int /*<<< orphan*/  ctx_dma; } ;
struct caam_hash_ctx {scalar_t__ ctx_len; int /*<<< orphan*/  sh_desc_update_dma; int /*<<< orphan*/  sh_desc_update; struct device* jrdev; } ;
struct TYPE_2__ {int flags; } ;
struct ahash_request {int nbytes; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct ahash_edesc {int src_nents; int sec4_sg_bytes; int /*<<< orphan*/  sec4_sg_dma; scalar_t__ sec4_sg; int /*<<< orphan*/ * hw_desc; } ;
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
 int /*<<< orphan*/  ahash_done_bi ; 
 struct ahash_edesc* ahash_edesc_alloc (struct caam_hash_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct caam_hash_state* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_unmap_ctx (struct device*,struct ahash_edesc*,struct ahash_request*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alt_buf (struct caam_hash_state*) ; 
 int* alt_buflen (struct caam_hash_state*) ; 
 int /*<<< orphan*/  append_seq_in_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_seq_out_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int buf_map_to_sec4_sg (struct device*,scalar_t__,struct caam_hash_state*) ; 
 int caam_jr_enqueue (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ahash_request*) ; 
 struct caam_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int crypto_tfm_alg_blocksize (int /*<<< orphan*/ *) ; 
 int ctx_map_to_sec4_sg (struct device*,struct caam_hash_state*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * current_buf (struct caam_hash_state*) ; 
 int* current_buflen (struct caam_hash_state*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dma_map_sg (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ahash_edesc*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int sg_nents_for_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_to_sec4_set_last (scalar_t__) ; 
 int /*<<< orphan*/  sg_to_sec4_sg_last (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahash_update_ctx(struct ahash_request *req)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	struct caam_hash_state *state = ahash_request_ctx(req);
	struct device *jrdev = ctx->jrdev;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	u8 *buf = current_buf(state);
	int *buflen = current_buflen(state);
	u8 *next_buf = alt_buf(state);
	int *next_buflen = alt_buflen(state), last_buflen;
	int in_len = *buflen + req->nbytes, to_hash;
	u32 *desc;
	int src_nents, mapped_nents, sec4_sg_bytes, sec4_sg_src_index;
	struct ahash_edesc *edesc;
	int ret = 0;

	last_buflen = *next_buflen;
	*next_buflen = in_len & (crypto_tfm_alg_blocksize(&ahash->base) - 1);
	to_hash = in_len - *next_buflen;

	if (to_hash) {
		src_nents = sg_nents_for_len(req->src,
					     req->nbytes - (*next_buflen));
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

		sec4_sg_src_index = 1 + (*buflen ? 1 : 0);
		sec4_sg_bytes = (sec4_sg_src_index + mapped_nents) *
				 sizeof(struct sec4_sg_entry);

		/*
		 * allocate space for base edesc and hw desc commands,
		 * link tables
		 */
		edesc = ahash_edesc_alloc(ctx, sec4_sg_src_index + mapped_nents,
					  ctx->sh_desc_update,
					  ctx->sh_desc_update_dma, flags);
		if (!edesc) {
			dma_unmap_sg(jrdev, req->src, src_nents, DMA_TO_DEVICE);
			return -ENOMEM;
		}

		edesc->src_nents = src_nents;
		edesc->sec4_sg_bytes = sec4_sg_bytes;

		ret = ctx_map_to_sec4_sg(jrdev, state, ctx->ctx_len,
					 edesc->sec4_sg, DMA_BIDIRECTIONAL);
		if (ret)
			goto unmap_ctx;

		ret = buf_map_to_sec4_sg(jrdev, edesc->sec4_sg + 1, state);
		if (ret)
			goto unmap_ctx;

		if (mapped_nents) {
			sg_to_sec4_sg_last(req->src, mapped_nents,
					   edesc->sec4_sg + sec4_sg_src_index,
					   0);
			if (*next_buflen)
				scatterwalk_map_and_copy(next_buf, req->src,
							 to_hash - *buflen,
							 *next_buflen, 0);
		} else {
			sg_to_sec4_set_last(edesc->sec4_sg + sec4_sg_src_index -
					    1);
		}

		desc = edesc->hw_desc;

		edesc->sec4_sg_dma = dma_map_single(jrdev, edesc->sec4_sg,
						     sec4_sg_bytes,
						     DMA_TO_DEVICE);
		if (dma_mapping_error(jrdev, edesc->sec4_sg_dma)) {
			dev_err(jrdev, "unable to map S/G table\n");
			ret = -ENOMEM;
			goto unmap_ctx;
		}

		append_seq_in_ptr(desc, edesc->sec4_sg_dma, ctx->ctx_len +
				       to_hash, LDST_SGF);

		append_seq_out_ptr(desc, state->ctx_dma, ctx->ctx_len, 0);

#ifdef DEBUG
		print_hex_dump(KERN_ERR, "jobdesc@"__stringify(__LINE__)": ",
			       DUMP_PREFIX_ADDRESS, 16, 4, desc,
			       desc_bytes(desc), 1);
#endif

		ret = caam_jr_enqueue(jrdev, desc, ahash_done_bi, req);
		if (ret)
			goto unmap_ctx;

		ret = -EINPROGRESS;
	} else if (*next_buflen) {
		scatterwalk_map_and_copy(buf + *buflen, req->src, 0,
					 req->nbytes, 0);
		*buflen = *next_buflen;
		*next_buflen = last_buflen;
	}
#ifdef DEBUG
	print_hex_dump(KERN_ERR, "buf@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, buf, *buflen, 1);
	print_hex_dump(KERN_ERR, "next buf@"__stringify(__LINE__)": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, next_buf,
		       *next_buflen, 1);
#endif

	return ret;
 unmap_ctx:
	ahash_unmap_ctx(jrdev, edesc, req, ctx->ctx_len, DMA_BIDIRECTIONAL);
	kfree(edesc);
	return ret;
}