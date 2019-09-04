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
struct rk_crypto_info {int dummy; } ;
struct rk_cipher_ctx {int /*<<< orphan*/  mode; struct rk_crypto_info* dev; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK_CRYPTO_AES_ECB_MODE ; 
 struct rk_cipher_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int rk_handle_req (struct rk_crypto_info*,struct ablkcipher_request*) ; 

__attribute__((used)) static int rk_aes_ecb_encrypt(struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct rk_cipher_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	struct rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_AES_ECB_MODE;
	return rk_handle_req(dev, req);
}