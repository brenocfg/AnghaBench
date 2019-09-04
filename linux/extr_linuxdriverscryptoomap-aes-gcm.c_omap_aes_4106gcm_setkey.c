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
struct omap_aes_ctx {unsigned int keylen; int /*<<< orphan*/  nonce; int /*<<< orphan*/  key; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 unsigned int AES_KEYSIZE_128 ; 
 unsigned int AES_KEYSIZE_192 ; 
 unsigned int AES_KEYSIZE_256 ; 
 int EINVAL ; 
 struct omap_aes_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

int omap_aes_4106gcm_setkey(struct crypto_aead *tfm, const u8 *key,
			    unsigned int keylen)
{
	struct omap_aes_ctx *ctx = crypto_aead_ctx(tfm);

	if (keylen < 4)
		return -EINVAL;

	keylen -= 4;
	if (keylen != AES_KEYSIZE_128 && keylen != AES_KEYSIZE_192 &&
	    keylen != AES_KEYSIZE_256)
		return -EINVAL;

	memcpy(ctx->key, key, keylen);
	memcpy(ctx->nonce, key + keylen, 4);
	ctx->keylen = keylen;

	return 0;
}