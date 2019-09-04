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
struct morus640_ctx {int /*<<< orphan*/  key; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 unsigned int MORUS640_BLOCK_SIZE ; 
 struct morus640_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_morus640_load (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int crypto_morus640_setkey(struct crypto_aead *aead, const u8 *key,
				  unsigned int keylen)
{
	struct morus640_ctx *ctx = crypto_aead_ctx(aead);

	if (keylen != MORUS640_BLOCK_SIZE) {
		crypto_aead_set_flags(aead, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	crypto_morus640_load(&ctx->key, key);
	return 0;
}