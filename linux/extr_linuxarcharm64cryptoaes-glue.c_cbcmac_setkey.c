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
struct mac_tfm_ctx {int /*<<< orphan*/  key; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int aes_expandkey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 struct mac_tfm_ctx* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_shash_set_flags (struct crypto_shash*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbcmac_setkey(struct crypto_shash *tfm, const u8 *in_key,
			 unsigned int key_len)
{
	struct mac_tfm_ctx *ctx = crypto_shash_ctx(tfm);
	int err;

	err = aes_expandkey(&ctx->key, in_key, key_len);
	if (err)
		crypto_shash_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);

	return err;
}