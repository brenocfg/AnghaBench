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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; int /*<<< orphan*/  flags; } ;
struct skcipher_request {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; int /*<<< orphan*/  iv; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_rfc3686_req_ctx {int /*<<< orphan*/ * iv; struct skcipher_request subreq; } ;
struct crypto_rfc3686_ctx {int /*<<< orphan*/  nonce; struct crypto_skcipher* child; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CTR_RFC3686_IV_SIZE ; 
 int CTR_RFC3686_NONCE_SIZE ; 
 scalar_t__ PTR_ALIGN (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 unsigned long crypto_skcipher_alignmask (struct crypto_skcipher*) ; 
 struct crypto_rfc3686_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_encrypt (struct skcipher_request*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,struct crypto_skcipher*) ; 

__attribute__((used)) static int crypto_rfc3686_crypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct crypto_rfc3686_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_skcipher *child = ctx->child;
	unsigned long align = crypto_skcipher_alignmask(tfm);
	struct crypto_rfc3686_req_ctx *rctx =
		(void *)PTR_ALIGN((u8 *)skcipher_request_ctx(req), align + 1);
	struct skcipher_request *subreq = &rctx->subreq;
	u8 *iv = rctx->iv;

	/* set up counter block */
	memcpy(iv, ctx->nonce, CTR_RFC3686_NONCE_SIZE);
	memcpy(iv + CTR_RFC3686_NONCE_SIZE, req->iv, CTR_RFC3686_IV_SIZE);

	/* initialize counter portion of counter block */
	*(__be32 *)(iv + CTR_RFC3686_NONCE_SIZE + CTR_RFC3686_IV_SIZE) =
		cpu_to_be32(1);

	skcipher_request_set_tfm(subreq, child);
	skcipher_request_set_callback(subreq, req->base.flags,
				      req->base.complete, req->base.data);
	skcipher_request_set_crypt(subreq, req->src, req->dst,
				   req->cryptlen, iv);

	return crypto_skcipher_encrypt(subreq);
}