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
struct crypto_async_request {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct ccp_sha_req_ctx {unsigned int hash_rem; unsigned int nbytes; unsigned int buf_count; int /*<<< orphan*/  data_sg; int /*<<< orphan*/  ctx; scalar_t__ final; int /*<<< orphan*/  src; int /*<<< orphan*/  buf; } ;
struct ahash_request {scalar_t__ result; } ;

/* Variables and functions */
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct ccp_sha_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 unsigned int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccp_sha_complete(struct crypto_async_request *async_req, int ret)
{
	struct ahash_request *req = ahash_request_cast(async_req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct ccp_sha_req_ctx *rctx = ahash_request_ctx(req);
	unsigned int digest_size = crypto_ahash_digestsize(tfm);

	if (ret)
		goto e_free;

	if (rctx->hash_rem) {
		/* Save remaining data to buffer */
		unsigned int offset = rctx->nbytes - rctx->hash_rem;

		scatterwalk_map_and_copy(rctx->buf, rctx->src,
					 offset, rctx->hash_rem, 0);
		rctx->buf_count = rctx->hash_rem;
	} else {
		rctx->buf_count = 0;
	}

	/* Update result area if supplied */
	if (req->result && rctx->final)
		memcpy(req->result, rctx->ctx, digest_size);

e_free:
	sg_free_table(&rctx->data_sg);

	return ret;
}