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
struct TYPE_2__ {int flags; } ;
struct skcipher_request {scalar_t__ cryptlen; int /*<<< orphan*/  iv; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct rctx {unsigned int left; int /*<<< orphan*/  t; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/ * ext; struct skcipher_request subreq; } ;
struct priv {int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  crypto_completion_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LRW_BUFFER_SIZE ; 
 scalar_t__ PAGE_SIZE ; 
 struct priv* crypto_skcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  gf128mul_64k_bbe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int min (scalar_t__,unsigned int) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int,int /*<<< orphan*/ ,struct skcipher_request*) ; 

__attribute__((used)) static int init_crypt(struct skcipher_request *req, crypto_completion_t done)
{
	struct priv *ctx = crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	struct rctx *rctx = skcipher_request_ctx(req);
	struct skcipher_request *subreq;
	gfp_t gfp;

	subreq = &rctx->subreq;
	skcipher_request_set_callback(subreq, req->base.flags, done, req);

	gfp = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
							   GFP_ATOMIC;
	rctx->ext = NULL;

	subreq->cryptlen = LRW_BUFFER_SIZE;
	if (req->cryptlen > LRW_BUFFER_SIZE) {
		unsigned int n = min(req->cryptlen, (unsigned int)PAGE_SIZE);

		rctx->ext = kmalloc(n, gfp);
		if (rctx->ext)
			subreq->cryptlen = n;
	}

	rctx->src = req->src;
	rctx->dst = req->dst;
	rctx->left = req->cryptlen;

	/* calculate first value of T */
	memcpy(&rctx->t, req->iv, sizeof(rctx->t));

	/* T <- I*Key2 */
	gf128mul_64k_bbe(&rctx->t, ctx->table);

	return 0;
}