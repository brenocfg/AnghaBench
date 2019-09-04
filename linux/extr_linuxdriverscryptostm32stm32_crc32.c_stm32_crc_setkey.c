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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_crc_ctx {int /*<<< orphan*/  key; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 struct stm32_crc_ctx* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_shash_set_flags (struct crypto_shash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int stm32_crc_setkey(struct crypto_shash *tfm, const u8 *key,
			    unsigned int keylen)
{
	struct stm32_crc_ctx *mctx = crypto_shash_ctx(tfm);

	if (keylen != sizeof(u32)) {
		crypto_shash_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	mctx->key = get_unaligned_le32(key);
	return 0;
}