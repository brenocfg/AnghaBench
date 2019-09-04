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
struct crypto_aead {int dummy; } ;
struct caam_ctx {int /*<<< orphan*/  qidev; } ;
struct aead_request {int dummy; } ;
struct aead_edesc {int /*<<< orphan*/  drv_req; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINPROGRESS ; 
 scalar_t__ IS_ERR_OR_NULL (struct aead_edesc*) ; 
 int PTR_ERR (struct aead_edesc*) ; 
 struct aead_edesc* aead_edesc_alloc (struct aead_request*,int) ; 
 int /*<<< orphan*/  aead_unmap (int /*<<< orphan*/ ,struct aead_edesc*,struct aead_request*) ; 
 int /*<<< orphan*/  caam_congested ; 
 int caam_qi_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  qi_cache_free (struct aead_edesc*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int aead_crypt(struct aead_request *req, bool encrypt)
{
	struct aead_edesc *edesc;
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	int ret;

	if (unlikely(caam_congested))
		return -EAGAIN;

	/* allocate extended descriptor */
	edesc = aead_edesc_alloc(req, encrypt);
	if (IS_ERR_OR_NULL(edesc))
		return PTR_ERR(edesc);

	/* Create and submit job descriptor */
	ret = caam_qi_enqueue(ctx->qidev, &edesc->drv_req);
	if (!ret) {
		ret = -EINPROGRESS;
	} else {
		aead_unmap(ctx->qidev, edesc, req);
		qi_cache_free(edesc);
	}

	return ret;
}