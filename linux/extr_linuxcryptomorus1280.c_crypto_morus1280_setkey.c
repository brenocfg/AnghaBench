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
union morus1280_block_in {int /*<<< orphan*/  const* bytes; } ;
typedef  int /*<<< orphan*/  u8 ;
struct morus1280_ctx {int /*<<< orphan*/  key; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 unsigned int MORUS1280_BLOCK_SIZE ; 
 struct morus1280_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_morus1280_load (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int crypto_morus1280_setkey(struct crypto_aead *aead, const u8 *key,
				   unsigned int keylen)
{
	struct morus1280_ctx *ctx = crypto_aead_ctx(aead);
	union morus1280_block_in tmp;

	if (keylen == MORUS1280_BLOCK_SIZE)
		crypto_morus1280_load(&ctx->key, key);
	else if (keylen == MORUS1280_BLOCK_SIZE / 2) {
		memcpy(tmp.bytes, key, keylen);
		memcpy(tmp.bytes + keylen, key, keylen);

		crypto_morus1280_load(&ctx->key, tmp.bytes);
	} else {
		crypto_aead_set_flags(aead, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	return 0;
}