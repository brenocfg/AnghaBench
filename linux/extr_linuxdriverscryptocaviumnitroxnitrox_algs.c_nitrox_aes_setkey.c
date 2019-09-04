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
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int flexi_aes_keylen (unsigned int) ; 
 int nitrox_skcipher_setkey (struct crypto_skcipher*,int,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int nitrox_aes_setkey(struct crypto_skcipher *cipher, const u8 *key,
			     unsigned int keylen)
{
	int aes_keylen;

	aes_keylen = flexi_aes_keylen(keylen);
	if (aes_keylen < 0) {
		crypto_skcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
	return nitrox_skcipher_setkey(cipher, aes_keylen, key, keylen);
}