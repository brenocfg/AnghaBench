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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_gcm_ghash_ctx {unsigned int cryptlen; int /*<<< orphan*/  complete; int /*<<< orphan*/  src; } ;
struct crypto_gcm_req_priv_ctx {int /*<<< orphan*/  src; struct crypto_gcm_ghash_ctx ghash_ctx; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int cryptlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_gcm_init_common (struct aead_request*) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  gcm_dec_hash_continue ; 
 int gcm_hash (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_gcm_decrypt(struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	struct crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	unsigned int authsize = crypto_aead_authsize(aead);
	unsigned int cryptlen = req->cryptlen;
	u32 flags = aead_request_flags(req);

	cryptlen -= authsize;

	crypto_gcm_init_common(req);

	gctx->src = sg_next(pctx->src);
	gctx->cryptlen = cryptlen;
	gctx->complete = gcm_dec_hash_continue;

	return gcm_hash(req, flags);
}