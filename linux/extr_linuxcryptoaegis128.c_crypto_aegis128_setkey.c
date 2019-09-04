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
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bytes; } ;
struct aegis_ctx {TYPE_1__ key; } ;

/* Variables and functions */
 unsigned int AEGIS128_KEY_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 struct aegis_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int crypto_aegis128_setkey(struct crypto_aead *aead, const u8 *key,
				  unsigned int keylen)
{
	struct aegis_ctx *ctx = crypto_aead_ctx(aead);

	if (keylen != AEGIS128_KEY_SIZE) {
		crypto_aead_set_flags(aead, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	memcpy(ctx->key.bytes, key, AEGIS128_KEY_SIZE);
	return 0;
}