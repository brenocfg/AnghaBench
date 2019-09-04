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
typedef  int /*<<< orphan*/  u32 ;
struct skcipher_request {int dummy; } ;
struct TYPE_2__ {struct skcipher_request skreq; } ;
struct crypto_gcm_req_priv_ctx {TYPE_1__ u; } ;
struct aead_request {int /*<<< orphan*/  cryptlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  aead_request_flags (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_gcm_init_common (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_gcm_init_crypt (struct aead_request*,int /*<<< orphan*/ ) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 scalar_t__ crypto_skcipher_encrypt (struct skcipher_request*) ; 
 int gcm_encrypt_continue (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcm_encrypt_done ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 

__attribute__((used)) static int crypto_gcm_encrypt(struct aead_request *req)
{
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	struct skcipher_request *skreq = &pctx->u.skreq;
	u32 flags = aead_request_flags(req);

	crypto_gcm_init_common(req);
	crypto_gcm_init_crypt(req, req->cryptlen);
	skcipher_request_set_callback(skreq, flags, gcm_encrypt_done, req);

	return crypto_skcipher_encrypt(skreq) ?:
	       gcm_encrypt_continue(req, flags);
}