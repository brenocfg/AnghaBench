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
struct skcipher_request {int /*<<< orphan*/  iv; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_fpu_ctx {struct crypto_skcipher* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,struct crypto_skcipher*) ; 
 struct crypto_fpu_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (int /*<<< orphan*/ ,struct crypto_skcipher*) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreq ; 

__attribute__((used)) static int crypto_fpu_encrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct crypto_fpu_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_skcipher *child = ctx->child;
	SKCIPHER_REQUEST_ON_STACK(subreq, child);
	int err;

	skcipher_request_set_tfm(subreq, child);
	skcipher_request_set_callback(subreq, 0, NULL, NULL);
	skcipher_request_set_crypt(subreq, req->src, req->dst, req->cryptlen,
				   req->iv);

	kernel_fpu_begin();
	err = crypto_skcipher_encrypt(subreq);
	kernel_fpu_end();

	skcipher_request_zero(subreq);
	return err;
}