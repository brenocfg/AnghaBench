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
struct crypto_skcipher {int reqsize; } ;
struct artpec6_cryptotfm_context {int /*<<< orphan*/  crypto_type; } ;
struct artpec6_crypto_request_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARTPEC6_CRYPTO_CIPHER_AES_XTS ; 
 struct artpec6_cryptotfm_context* crypto_skcipher_ctx (struct crypto_skcipher*) ; 

__attribute__((used)) static int artpec6_crypto_aes_xts_init(struct crypto_skcipher *tfm)
{
	struct artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(tfm);

	tfm->reqsize = sizeof(struct artpec6_crypto_request_context);
	ctx->crypto_type = ARTPEC6_CRYPTO_CIPHER_AES_XTS;

	return 0;
}