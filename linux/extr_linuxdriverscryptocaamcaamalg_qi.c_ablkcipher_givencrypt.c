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
struct ablkcipher_request {int dummy; } ;
struct skcipher_givcrypt_request {struct ablkcipher_request creq; } ;
struct crypto_ablkcipher {int dummy; } ;
struct caam_ctx {int /*<<< orphan*/  qidev; } ;
struct ablkcipher_edesc {int /*<<< orphan*/  drv_req; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINPROGRESS ; 
 scalar_t__ IS_ERR (struct ablkcipher_edesc*) ; 
 int PTR_ERR (struct ablkcipher_edesc*) ; 
 struct ablkcipher_edesc* ablkcipher_giv_edesc_alloc (struct skcipher_givcrypt_request*) ; 
 int /*<<< orphan*/  ablkcipher_unmap (int /*<<< orphan*/ ,struct ablkcipher_edesc*,struct ablkcipher_request*) ; 
 int /*<<< orphan*/  caam_congested ; 
 int caam_qi_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct caam_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  qi_cache_free (struct ablkcipher_edesc*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ablkcipher_givencrypt(struct skcipher_givcrypt_request *creq)
{
	struct ablkcipher_request *req = &creq->creq;
	struct ablkcipher_edesc *edesc;
	struct crypto_ablkcipher *ablkcipher = crypto_ablkcipher_reqtfm(req);
	struct caam_ctx *ctx = crypto_ablkcipher_ctx(ablkcipher);
	int ret;

	if (unlikely(caam_congested))
		return -EAGAIN;

	/* allocate extended descriptor */
	edesc = ablkcipher_giv_edesc_alloc(creq);
	if (IS_ERR(edesc))
		return PTR_ERR(edesc);

	ret = caam_qi_enqueue(ctx->qidev, &edesc->drv_req);
	if (!ret) {
		ret = -EINPROGRESS;
	} else {
		ablkcipher_unmap(ctx->qidev, edesc, req);
		qi_cache_free(edesc);
	}

	return ret;
}