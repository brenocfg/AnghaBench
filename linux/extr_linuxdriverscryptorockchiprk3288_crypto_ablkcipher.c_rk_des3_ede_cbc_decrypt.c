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
struct rk_cipher_ctx {int mode; struct rk_crypto_info* dev; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int RK_CRYPTO_DEC ; 
 int RK_CRYPTO_TDES_CHAINMODE_CBC ; 
 int RK_CRYPTO_TDES_SELECT ; 
 struct rk_cipher_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int rk_handle_req (struct rk_crypto_info*,struct ablkcipher_request*) ; 

__attribute__((used)) static int rk_des3_ede_cbc_decrypt(struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct rk_cipher_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	struct rk_crypto_info *dev = ctx->dev;

	ctx->mode = RK_CRYPTO_TDES_SELECT | RK_CRYPTO_TDES_CHAINMODE_CBC |
		    RK_CRYPTO_DEC;
	return rk_handle_req(dev, req);
}