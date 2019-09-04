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
struct sec4_sg_entry {int dummy; } ;
typedef  struct sec4_sg_entry u8 ;
struct TYPE_2__ {int flags; } ;
struct ablkcipher_request {scalar_t__ src; scalar_t__ dst; int /*<<< orphan*/  nbytes; TYPE_1__ base; } ;
struct skcipher_givcrypt_request {struct ablkcipher_request creq; } ;
struct device {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct caam_ctx {struct device* jrdev; } ;
struct ablkcipher_edesc {int src_nents; int dst_nents; int sec4_sg_bytes; void* iv_dma; void* sec4_sg_dma; struct sec4_sg_entry* sec4_sg; scalar_t__ hw_desc; int /*<<< orphan*/  iv_dir; } ;
typedef  int gfp_t ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 struct ablkcipher_edesc* ERR_PTR (int) ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  caam_unmap (struct device*,scalar_t__,scalar_t__,int,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct caam_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int dma_map_sg (struct device*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 void* dma_map_single (struct device*,struct sec4_sg_entry*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,void*) ; 
 int /*<<< orphan*/  dma_to_sec4_sg_one (struct sec4_sg_entry*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ablkcipher_edesc*) ; 
 struct ablkcipher_edesc* kzalloc (int,int) ; 
 scalar_t__ likely (int) ; 
 int sg_nents_for_len (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_to_sec4_sg_last (scalar_t__,int,struct sec4_sg_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ablkcipher_edesc *ablkcipher_giv_edesc_alloc(
				struct skcipher_givcrypt_request *greq,
				int desc_bytes)
{
	struct ablkcipher_request *req = &greq->creq;
	struct crypto_ablkcipher *ablkcipher = crypto_ablkcipher_reqtfm(req);
	struct caam_ctx *ctx = crypto_ablkcipher_ctx(ablkcipher);
	struct device *jrdev = ctx->jrdev;
	gfp_t flags = (req->base.flags &  CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	int src_nents, mapped_src_nents, dst_nents, mapped_dst_nents;
	struct ablkcipher_edesc *edesc;
	dma_addr_t iv_dma;
	u8 *iv;
	int ivsize = crypto_ablkcipher_ivsize(ablkcipher);
	int dst_sg_idx, sec4_sg_ents, sec4_sg_bytes;

	src_nents = sg_nents_for_len(req->src, req->nbytes);
	if (unlikely(src_nents < 0)) {
		dev_err(jrdev, "Insufficient bytes (%d) in src S/G\n",
			req->nbytes);
		return ERR_PTR(src_nents);
	}

	if (likely(req->src == req->dst)) {
		mapped_src_nents = dma_map_sg(jrdev, req->src, src_nents,
					      DMA_BIDIRECTIONAL);
		if (unlikely(!mapped_src_nents)) {
			dev_err(jrdev, "unable to map source\n");
			return ERR_PTR(-ENOMEM);
		}

		dst_nents = src_nents;
		mapped_dst_nents = src_nents;
	} else {
		mapped_src_nents = dma_map_sg(jrdev, req->src, src_nents,
					      DMA_TO_DEVICE);
		if (unlikely(!mapped_src_nents)) {
			dev_err(jrdev, "unable to map source\n");
			return ERR_PTR(-ENOMEM);
		}

		dst_nents = sg_nents_for_len(req->dst, req->nbytes);
		if (unlikely(dst_nents < 0)) {
			dev_err(jrdev, "Insufficient bytes (%d) in dst S/G\n",
				req->nbytes);
			return ERR_PTR(dst_nents);
		}

		mapped_dst_nents = dma_map_sg(jrdev, req->dst, dst_nents,
					      DMA_FROM_DEVICE);
		if (unlikely(!mapped_dst_nents)) {
			dev_err(jrdev, "unable to map destination\n");
			dma_unmap_sg(jrdev, req->src, src_nents, DMA_TO_DEVICE);
			return ERR_PTR(-ENOMEM);
		}
	}

	sec4_sg_ents = mapped_src_nents > 1 ? mapped_src_nents : 0;
	dst_sg_idx = sec4_sg_ents;
	sec4_sg_ents += 1 + mapped_dst_nents;

	/*
	 * allocate space for base edesc and hw desc commands, link tables, IV
	 */
	sec4_sg_bytes = sec4_sg_ents * sizeof(struct sec4_sg_entry);
	edesc = kzalloc(sizeof(*edesc) + desc_bytes + sec4_sg_bytes + ivsize,
			GFP_DMA | flags);
	if (!edesc) {
		dev_err(jrdev, "could not allocate extended descriptor\n");
		caam_unmap(jrdev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		return ERR_PTR(-ENOMEM);
	}

	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;
	edesc->sec4_sg_bytes = sec4_sg_bytes;
	edesc->sec4_sg = (struct sec4_sg_entry *)((u8 *)edesc->hw_desc +
						  desc_bytes);
	edesc->iv_dir = DMA_FROM_DEVICE;

	/* Make sure IV is located in a DMAable area */
	iv = (u8 *)edesc->hw_desc + desc_bytes + sec4_sg_bytes;
	iv_dma = dma_map_single(jrdev, iv, ivsize, DMA_FROM_DEVICE);
	if (dma_mapping_error(jrdev, iv_dma)) {
		dev_err(jrdev, "unable to map IV\n");
		caam_unmap(jrdev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, DMA_NONE, 0, 0);
		kfree(edesc);
		return ERR_PTR(-ENOMEM);
	}

	if (mapped_src_nents > 1)
		sg_to_sec4_sg_last(req->src, mapped_src_nents, edesc->sec4_sg,
				   0);

	dma_to_sec4_sg_one(edesc->sec4_sg + dst_sg_idx, iv_dma, ivsize, 0);
	sg_to_sec4_sg_last(req->dst, mapped_dst_nents, edesc->sec4_sg +
			   dst_sg_idx + 1, 0);

	edesc->sec4_sg_dma = dma_map_single(jrdev, edesc->sec4_sg,
					    sec4_sg_bytes, DMA_TO_DEVICE);
	if (dma_mapping_error(jrdev, edesc->sec4_sg_dma)) {
		dev_err(jrdev, "unable to map S/G table\n");
		caam_unmap(jrdev, req->src, req->dst, src_nents, dst_nents,
			   iv_dma, ivsize, DMA_FROM_DEVICE, 0, 0);
		kfree(edesc);
		return ERR_PTR(-ENOMEM);
	}
	edesc->iv_dma = iv_dma;

#ifdef DEBUG
	print_hex_dump(KERN_ERR,
		       "ablkcipher sec4_sg@" __stringify(__LINE__) ": ",
		       DUMP_PREFIX_ADDRESS, 16, 4, edesc->sec4_sg,
		       sec4_sg_bytes, 1);
#endif

	return edesc;
}