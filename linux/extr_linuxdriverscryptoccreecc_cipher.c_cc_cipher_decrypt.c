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
struct skcipher_request {unsigned int cryptlen; int /*<<< orphan*/  src; int /*<<< orphan*/  base; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct cipher_req_ctx {int /*<<< orphan*/  backup_info; } ;
struct cc_cipher_ctx {scalar_t__ cipher_mode; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ DRV_CIPHER_CBC ; 
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_DECRYPT ; 
 int ENOMEM ; 
 int cc_cipher_process (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_gfp_flags (int /*<<< orphan*/ *) ; 
 unsigned int crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct crypto_tfm* crypto_skcipher_tfm (struct crypto_skcipher*) ; 
 struct cc_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cipher_req_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 struct cipher_req_ctx* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static int cc_cipher_decrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *sk_tfm = crypto_skcipher_reqtfm(req);
	struct crypto_tfm *tfm = crypto_skcipher_tfm(sk_tfm);
	struct cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	struct cipher_req_ctx *req_ctx = skcipher_request_ctx(req);
	unsigned int ivsize = crypto_skcipher_ivsize(sk_tfm);
	gfp_t flags = cc_gfp_flags(&req->base);
	unsigned int len;

	memset(req_ctx, 0, sizeof(*req_ctx));

	if ((ctx_p->cipher_mode == DRV_CIPHER_CBC) &&
	    (req->cryptlen >= ivsize)) {

		/* Allocate and save the last IV sized bytes of the source,
		 * which will be lost in case of in-place decryption.
		 */
		req_ctx->backup_info = kzalloc(ivsize, flags);
		if (!req_ctx->backup_info)
			return -ENOMEM;

		len = req->cryptlen - ivsize;
		scatterwalk_map_and_copy(req_ctx->backup_info, req->src, len,
					 ivsize, 0);
	}

	return cc_cipher_process(req, DRV_CRYPTO_DIRECTION_DECRYPT);
}