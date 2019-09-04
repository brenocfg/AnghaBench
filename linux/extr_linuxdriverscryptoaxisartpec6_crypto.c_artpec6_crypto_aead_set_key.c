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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_aead {int /*<<< orphan*/  base; } ;
struct artpec6_cryptotfm_context {unsigned int key_length; int /*<<< orphan*/  aes_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 struct artpec6_cryptotfm_context* crypto_tfm_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int artpec6_crypto_aead_set_key(struct crypto_aead *tfm, const u8 *key,
			       unsigned int len)
{
	struct artpec6_cryptotfm_context *ctx = crypto_tfm_ctx(&tfm->base);

	if (len != 16 && len != 24 && len != 32) {
		crypto_aead_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -1;
	}

	ctx->key_length = len;

	memcpy(ctx->aes_key, key, len);
	return 0;
}