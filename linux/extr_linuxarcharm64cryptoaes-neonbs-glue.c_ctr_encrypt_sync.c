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
struct skcipher_request {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct aesbs_ctr_ctx {int /*<<< orphan*/  fallback; } ;

/* Variables and functions */
 int aes_ctr_encrypt_fallback (int /*<<< orphan*/ *,struct skcipher_request*) ; 
 struct aesbs_ctr_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int ctr_encrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  may_use_simd () ; 

__attribute__((used)) static int ctr_encrypt_sync(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct aesbs_ctr_ctx *ctx = crypto_skcipher_ctx(tfm);

	if (!may_use_simd())
		return aes_ctr_encrypt_fallback(&ctx->fallback, req);

	return ctr_encrypt(req);
}