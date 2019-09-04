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
struct talitos_ptr {int dummy; } ;
struct talitos_private {int dummy; } ;
struct talitos_desc {int hdr; struct talitos_ptr* ptr; } ;
struct talitos_edesc {int src_nents; unsigned int iv_dma; int dst_nents; int icv_ool; unsigned int dma_link_tbl; int /*<<< orphan*/  dma_len; struct talitos_ptr* link_tbl; int /*<<< orphan*/  buf; struct talitos_desc desc; } ;
struct talitos_ctx {unsigned int dma_key; unsigned int authkeylen; unsigned int enckeylen; int /*<<< orphan*/  ch; int /*<<< orphan*/  iv; struct device* dev; } ;
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int cryptlen; scalar_t__ src; unsigned int assoclen; scalar_t__ dst; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 int DESC_HDR_MODE1_MDEU_CICV ; 
 int DESC_HDR_TYPE_IPSEC_ESP ; 
 int /*<<< orphan*/  DESC_PTR_LNKTBL_RETURN ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINPROGRESS ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct talitos_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int dma_map_sg (struct device*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int has_ftr_sec1 (struct talitos_private*) ; 
 int /*<<< orphan*/  ipsec_esp_unmap (struct device*,struct talitos_edesc*,struct aead_request*) ; 
 int /*<<< orphan*/  kfree (struct talitos_edesc*) ; 
 int /*<<< orphan*/  map_single_talitos_ptr (struct device*,struct talitos_ptr*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (scalar_t__,int,int /*<<< orphan*/ ,unsigned int) ; 
 int talitos_sg_map (struct device*,scalar_t__,unsigned int,struct talitos_edesc*,struct talitos_ptr*,int,unsigned int,int) ; 
 int talitos_sg_map_ext (struct device*,scalar_t__,unsigned int,struct talitos_edesc*,struct talitos_ptr*,int,unsigned int,int,int) ; 
 int talitos_submit (struct device*,int /*<<< orphan*/ ,struct talitos_desc*,void (*) (struct device*,struct talitos_desc*,void*,int),struct aead_request*) ; 
 int /*<<< orphan*/  to_talitos_ptr (struct talitos_ptr*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  to_talitos_ptr_ext_or (struct talitos_ptr*,unsigned int,int) ; 
 int /*<<< orphan*/  to_talitos_ptr_ext_set (struct talitos_ptr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipsec_esp(struct talitos_edesc *edesc, struct aead_request *areq,
		     void (*callback)(struct device *dev,
				      struct talitos_desc *desc,
				      void *context, int error))
{
	struct crypto_aead *aead = crypto_aead_reqtfm(areq);
	unsigned int authsize = crypto_aead_authsize(aead);
	struct talitos_ctx *ctx = crypto_aead_ctx(aead);
	struct device *dev = ctx->dev;
	struct talitos_desc *desc = &edesc->desc;
	unsigned int cryptlen = areq->cryptlen;
	unsigned int ivsize = crypto_aead_ivsize(aead);
	int tbl_off = 0;
	int sg_count, ret;
	int elen = 0;
	bool sync_needed = false;
	struct talitos_private *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	bool is_ipsec_esp = desc->hdr & DESC_HDR_TYPE_IPSEC_ESP;
	struct talitos_ptr *civ_ptr = &desc->ptr[is_ipsec_esp ? 2 : 3];
	struct talitos_ptr *ckey_ptr = &desc->ptr[is_ipsec_esp ? 3 : 2];

	/* hmac key */
	to_talitos_ptr(&desc->ptr[0], ctx->dma_key, ctx->authkeylen, is_sec1);

	sg_count = edesc->src_nents ?: 1;
	if (is_sec1 && sg_count > 1)
		sg_copy_to_buffer(areq->src, sg_count, edesc->buf,
				  areq->assoclen + cryptlen);
	else
		sg_count = dma_map_sg(dev, areq->src, sg_count,
				      (areq->src == areq->dst) ?
				      DMA_BIDIRECTIONAL : DMA_TO_DEVICE);

	/* hmac data */
	ret = talitos_sg_map(dev, areq->src, areq->assoclen, edesc,
			     &desc->ptr[1], sg_count, 0, tbl_off);

	if (ret > 1) {
		tbl_off += ret;
		sync_needed = true;
	}

	/* cipher iv */
	to_talitos_ptr(civ_ptr, edesc->iv_dma, ivsize, is_sec1);

	/* cipher key */
	to_talitos_ptr(ckey_ptr, ctx->dma_key  + ctx->authkeylen,
		       ctx->enckeylen, is_sec1);

	/*
	 * cipher in
	 * map and adjust cipher len to aead request cryptlen.
	 * extent is bytes of HMAC postpended to ciphertext,
	 * typically 12 for ipsec
	 */
	if (is_ipsec_esp && (desc->hdr & DESC_HDR_MODE1_MDEU_CICV))
		elen = authsize;

	ret = talitos_sg_map_ext(dev, areq->src, cryptlen, edesc, &desc->ptr[4],
				 sg_count, areq->assoclen, tbl_off, elen);

	if (ret > 1) {
		tbl_off += ret;
		sync_needed = true;
	}

	/* cipher out */
	if (areq->src != areq->dst) {
		sg_count = edesc->dst_nents ? : 1;
		if (!is_sec1 || sg_count == 1)
			dma_map_sg(dev, areq->dst, sg_count, DMA_FROM_DEVICE);
	}

	ret = talitos_sg_map(dev, areq->dst, cryptlen, edesc, &desc->ptr[5],
			     sg_count, areq->assoclen, tbl_off);

	if (is_ipsec_esp)
		to_talitos_ptr_ext_or(&desc->ptr[5], authsize, is_sec1);

	/* ICV data */
	if (ret > 1) {
		tbl_off += ret;
		edesc->icv_ool = true;
		sync_needed = true;

		if (is_ipsec_esp) {
			struct talitos_ptr *tbl_ptr = &edesc->link_tbl[tbl_off];
			int offset = (edesc->src_nents + edesc->dst_nents + 2) *
				     sizeof(struct talitos_ptr) + authsize;

			/* Add an entry to the link table for ICV data */
			to_talitos_ptr_ext_set(tbl_ptr - 1, 0, is_sec1);
			to_talitos_ptr_ext_set(tbl_ptr, DESC_PTR_LNKTBL_RETURN,
					       is_sec1);

			/* icv data follows link tables */
			to_talitos_ptr(tbl_ptr, edesc->dma_link_tbl + offset,
				       authsize, is_sec1);
		} else {
			dma_addr_t addr = edesc->dma_link_tbl;

			if (is_sec1)
				addr += areq->assoclen + cryptlen;
			else
				addr += sizeof(struct talitos_ptr) * tbl_off;

			to_talitos_ptr(&desc->ptr[6], addr, authsize, is_sec1);
		}
	} else if (!is_ipsec_esp) {
		ret = talitos_sg_map(dev, areq->dst, authsize, edesc,
				     &desc->ptr[6], sg_count, areq->assoclen +
							      cryptlen,
				     tbl_off);
		if (ret > 1) {
			tbl_off += ret;
			edesc->icv_ool = true;
			sync_needed = true;
		} else {
			edesc->icv_ool = false;
		}
	} else {
		edesc->icv_ool = false;
	}

	/* iv out */
	if (is_ipsec_esp)
		map_single_talitos_ptr(dev, &desc->ptr[6], ivsize, ctx->iv,
				       DMA_FROM_DEVICE);

	if (sync_needed)
		dma_sync_single_for_device(dev, edesc->dma_link_tbl,
					   edesc->dma_len,
					   DMA_BIDIRECTIONAL);

	ret = talitos_submit(dev, ctx->ch, desc, callback, areq);
	if (ret != -EINPROGRESS) {
		ipsec_esp_unmap(dev, edesc, areq);
		kfree(edesc);
	}
	return ret;
}