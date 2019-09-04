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
struct crypto_async_request {struct aead_request* data; } ;
struct crypto_aead {int dummy; } ;
struct authenc_request_ctx {scalar_t__ tail; } ;
struct authenc_instance_ctx {scalar_t__ reqoff; } ;
struct ahash_request {int /*<<< orphan*/  result; } ;
struct aead_request {scalar_t__ cryptlen; scalar_t__ assoclen; int /*<<< orphan*/  dst; } ;
struct aead_instance {int dummy; } ;

/* Variables and functions */
 struct aead_instance* aead_alg_instance (struct crypto_aead*) ; 
 struct authenc_instance_ctx* aead_instance_ctx (struct aead_instance*) ; 
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 
 struct authenc_request_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void authenc_geniv_ahash_done(struct crypto_async_request *areq, int err)
{
	struct aead_request *req = areq->data;
	struct crypto_aead *authenc = crypto_aead_reqtfm(req);
	struct aead_instance *inst = aead_alg_instance(authenc);
	struct authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	struct authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	struct ahash_request *ahreq = (void *)(areq_ctx->tail + ictx->reqoff);

	if (err)
		goto out;

	scatterwalk_map_and_copy(ahreq->result, req->dst,
				 req->assoclen + req->cryptlen,
				 crypto_aead_authsize(authenc), 1);

out:
	aead_request_complete(req, err);
}