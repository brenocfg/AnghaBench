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
typedef  int u8 ;
struct scatterlist {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; int /*<<< orphan*/  flags; } ;
struct aead_request {scalar_t__ src; scalar_t__ dst; scalar_t__ assoclen; int /*<<< orphan*/  cryptlen; TYPE_1__ base; int /*<<< orphan*/  iv; } ;
struct crypto_rfc4309_req_ctx {struct scatterlist* dst; struct scatterlist* src; struct aead_request subreq; } ;
struct crypto_rfc4309_ctx {int /*<<< orphan*/  nonce; struct crypto_aead* child; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int* PTR_ALIGN (int*,scalar_t__) ; 
 struct crypto_rfc4309_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,scalar_t__) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,struct scatterlist*,struct scatterlist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,struct crypto_aead*) ; 
 scalar_t__ crypto_aead_alignmask (struct crypto_aead*) ; 
 struct crypto_rfc4309_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_reqsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 struct scatterlist* scatterwalk_ffwd (struct scatterlist*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_chain (struct scatterlist*,int,struct scatterlist*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int*,scalar_t__) ; 

__attribute__((used)) static struct aead_request *crypto_rfc4309_crypt(struct aead_request *req)
{
	struct crypto_rfc4309_req_ctx *rctx = aead_request_ctx(req);
	struct aead_request *subreq = &rctx->subreq;
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_rfc4309_ctx *ctx = crypto_aead_ctx(aead);
	struct crypto_aead *child = ctx->child;
	struct scatterlist *sg;
	u8 *iv = PTR_ALIGN((u8 *)(subreq + 1) + crypto_aead_reqsize(child),
			   crypto_aead_alignmask(child) + 1);

	/* L' */
	iv[0] = 3;

	memcpy(iv + 1, ctx->nonce, 3);
	memcpy(iv + 4, req->iv, 8);

	scatterwalk_map_and_copy(iv + 16, req->src, 0, req->assoclen - 8, 0);

	sg_init_table(rctx->src, 3);
	sg_set_buf(rctx->src, iv + 16, req->assoclen - 8);
	sg = scatterwalk_ffwd(rctx->src + 1, req->src, req->assoclen);
	if (sg != rctx->src + 1)
		sg_chain(rctx->src, 2, sg);

	if (req->src != req->dst) {
		sg_init_table(rctx->dst, 3);
		sg_set_buf(rctx->dst, iv + 16, req->assoclen - 8);
		sg = scatterwalk_ffwd(rctx->dst + 1, req->dst, req->assoclen);
		if (sg != rctx->dst + 1)
			sg_chain(rctx->dst, 2, sg);
	}

	aead_request_set_tfm(subreq, child);
	aead_request_set_callback(subreq, req->base.flags, req->base.complete,
				  req->base.data);
	aead_request_set_crypt(subreq, rctx->src,
			       req->src == req->dst ? rctx->src : rctx->dst,
			       req->cryptlen, iv);
	aead_request_set_ad(subreq, req->assoclen - 8);

	return subreq;
}