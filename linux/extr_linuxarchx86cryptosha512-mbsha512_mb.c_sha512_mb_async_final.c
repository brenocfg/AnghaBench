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
struct sha512_mb_ctx {struct mcryptd_ahash* mcryptd_tfm; } ;
struct mcryptd_ahash {int /*<<< orphan*/  base; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct ahash_request* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (struct ahash_request*,int /*<<< orphan*/ *) ; 
 struct sha512_mb_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_final (struct ahash_request*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (struct ahash_request*,struct ahash_request*,int) ; 

__attribute__((used)) static int sha512_mb_async_final(struct ahash_request *req)
{
	struct ahash_request *mcryptd_req = ahash_request_ctx(req);

	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct sha512_mb_ctx *ctx = crypto_ahash_ctx(tfm);
	struct mcryptd_ahash *mcryptd_tfm = ctx->mcryptd_tfm;

	memcpy(mcryptd_req, req, sizeof(*req));
	ahash_request_set_tfm(mcryptd_req, &mcryptd_tfm->base);
	return crypto_ahash_final(mcryptd_req);
}