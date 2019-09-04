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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct skcipher_request {scalar_t__ cryptlen; TYPE_1__ base; } ;
struct rctx {scalar_t__ left; struct skcipher_request subreq; } ;
struct crypto_async_request {struct skcipher_request* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EINPROGRESS ; 
 int do_decrypt (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_crypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_complete (struct skcipher_request*,int) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static void decrypt_done(struct crypto_async_request *areq, int err)
{
	struct skcipher_request *req = areq->data;
	struct skcipher_request *subreq;
	struct rctx *rctx;

	rctx = skcipher_request_ctx(req);

	if (err == -EINPROGRESS) {
		if (rctx->left != req->cryptlen)
			return;
		goto out;
	}

	subreq = &rctx->subreq;
	subreq->base.flags &= CRYPTO_TFM_REQ_MAY_BACKLOG;

	err = do_decrypt(req, err ?: post_crypt(req));
	if (rctx->left)
		return;

out:
	skcipher_request_complete(req, err);
}