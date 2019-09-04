#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ bytes; } ;
struct morus1280_ctx {TYPE_1__ key; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 unsigned int MORUS1280_BLOCK_SIZE ; 
 struct morus1280_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,unsigned int) ; 

int crypto_morus1280_glue_setkey(struct crypto_aead *aead, const u8 *key,
				 unsigned int keylen)
{
	struct morus1280_ctx *ctx = crypto_aead_ctx(aead);

	if (keylen == MORUS1280_BLOCK_SIZE) {
		memcpy(ctx->key.bytes, key, MORUS1280_BLOCK_SIZE);
	} else if (keylen == MORUS1280_BLOCK_SIZE / 2) {
		memcpy(ctx->key.bytes, key, keylen);
		memcpy(ctx->key.bytes + keylen, key, keylen);
	} else {
		crypto_aead_set_flags(aead, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	return 0;
}