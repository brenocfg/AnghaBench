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
struct rsa_edesc {int src_nents; int dst_nents; int sec4_sg_bytes; int /*<<< orphan*/  sec4_sg_dma; void* sec4_sg; } ;
struct device {int dummy; } ;
struct crypto_akcipher {int dummy; } ;
struct caam_rsa_req_ctx {int /*<<< orphan*/  src; } ;
struct caam_rsa_ctx {struct device* dev; } ;
struct TYPE_2__ {int flags; } ;
struct akcipher_request {int src_len; int dst_len; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; TYPE_1__ base; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 struct rsa_edesc* ERR_PTR (int) ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int SG_MITER_ATOMIC ; 
 struct caam_rsa_req_ctx* akcipher_request_ctx (struct akcipher_request*) ; 
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int caam_rsa_count_leading_zeros (int /*<<< orphan*/ ,int,int) ; 
 struct crypto_akcipher* crypto_akcipher_reqtfm (struct akcipher_request*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dma_map_sg (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rsa_edesc*) ; 
 struct rsa_edesc* kzalloc (int,int) ; 
 int /*<<< orphan*/  scatterwalk_ffwd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sg_nents_for_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_to_sec4_sg_last (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct rsa_edesc *rsa_edesc_alloc(struct akcipher_request *req,
					 size_t desclen)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct device *dev = ctx->dev;
	struct caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);
	struct rsa_edesc *edesc;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	int sg_flags = (flags == GFP_ATOMIC) ? SG_MITER_ATOMIC : 0;
	int sgc;
	int sec4_sg_index, sec4_sg_len = 0, sec4_sg_bytes;
	int src_nents, dst_nents;
	int lzeros;

	lzeros = caam_rsa_count_leading_zeros(req->src, req->src_len, sg_flags);
	if (lzeros < 0)
		return ERR_PTR(lzeros);

	req->src_len -= lzeros;
	req->src = scatterwalk_ffwd(req_ctx->src, req->src, lzeros);

	src_nents = sg_nents_for_len(req->src, req->src_len);
	dst_nents = sg_nents_for_len(req->dst, req->dst_len);

	if (src_nents > 1)
		sec4_sg_len = src_nents;
	if (dst_nents > 1)
		sec4_sg_len += dst_nents;

	sec4_sg_bytes = sec4_sg_len * sizeof(struct sec4_sg_entry);

	/* allocate space for base edesc, hw desc commands and link tables */
	edesc = kzalloc(sizeof(*edesc) + desclen + sec4_sg_bytes,
			GFP_DMA | flags);
	if (!edesc)
		return ERR_PTR(-ENOMEM);

	sgc = dma_map_sg(dev, req->src, src_nents, DMA_TO_DEVICE);
	if (unlikely(!sgc)) {
		dev_err(dev, "unable to map source\n");
		goto src_fail;
	}

	sgc = dma_map_sg(dev, req->dst, dst_nents, DMA_FROM_DEVICE);
	if (unlikely(!sgc)) {
		dev_err(dev, "unable to map destination\n");
		goto dst_fail;
	}

	edesc->sec4_sg = (void *)edesc + sizeof(*edesc) + desclen;

	sec4_sg_index = 0;
	if (src_nents > 1) {
		sg_to_sec4_sg_last(req->src, src_nents, edesc->sec4_sg, 0);
		sec4_sg_index += src_nents;
	}
	if (dst_nents > 1)
		sg_to_sec4_sg_last(req->dst, dst_nents,
				   edesc->sec4_sg + sec4_sg_index, 0);

	/* Save nents for later use in Job Descriptor */
	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;

	if (!sec4_sg_bytes)
		return edesc;

	edesc->sec4_sg_dma = dma_map_single(dev, edesc->sec4_sg,
					    sec4_sg_bytes, DMA_TO_DEVICE);
	if (dma_mapping_error(dev, edesc->sec4_sg_dma)) {
		dev_err(dev, "unable to map S/G table\n");
		goto sec4_sg_fail;
	}

	edesc->sec4_sg_bytes = sec4_sg_bytes;

	return edesc;

sec4_sg_fail:
	dma_unmap_sg(dev, req->dst, dst_nents, DMA_FROM_DEVICE);
dst_fail:
	dma_unmap_sg(dev, req->src, src_nents, DMA_TO_DEVICE);
src_fail:
	kfree(edesc);
	return ERR_PTR(-ENOMEM);
}