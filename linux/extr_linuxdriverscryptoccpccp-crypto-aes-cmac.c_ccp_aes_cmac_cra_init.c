#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_tfm {int dummy; } ;
struct crypto_cipher {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_3__ {struct crypto_cipher* tfm_cipher; scalar_t__ key_len; } ;
struct TYPE_4__ {TYPE_1__ aes; } ;
struct ccp_ctx {TYPE_2__ u; int /*<<< orphan*/  complete; } ;
struct ccp_aes_cmac_req_ctx {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (struct crypto_cipher*) ; 
 int PTR_ERR (struct crypto_cipher*) ; 
 struct crypto_ahash* __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  ccp_aes_cmac_complete ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (struct crypto_ahash*,int) ; 
 struct crypto_cipher* crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int) ; 
 struct ccp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int ccp_aes_cmac_cra_init(struct crypto_tfm *tfm)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(tfm);
	struct crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	struct crypto_cipher *cipher_tfm;

	ctx->complete = ccp_aes_cmac_complete;
	ctx->u.aes.key_len = 0;

	crypto_ahash_set_reqsize(ahash, sizeof(struct ccp_aes_cmac_req_ctx));

	cipher_tfm = crypto_alloc_cipher("aes", 0,
					 CRYPTO_ALG_ASYNC |
					 CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(cipher_tfm)) {
		pr_warn("could not load aes cipher driver\n");
		return PTR_ERR(cipher_tfm);
	}
	ctx->u.aes.tfm_cipher = cipher_tfm;

	return 0;
}