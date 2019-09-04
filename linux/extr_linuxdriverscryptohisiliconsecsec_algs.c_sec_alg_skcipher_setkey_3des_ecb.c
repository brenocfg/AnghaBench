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
 int DES_KEY_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  SEC_C_3DES_ECB_192_3KEY ; 
 int sec_alg_skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sec_alg_skcipher_setkey_3des_ecb(struct crypto_skcipher *tfm,
					    const u8 *key, unsigned int keylen)
{
	if (keylen != DES_KEY_SIZE * 3)
		return -EINVAL;

	return sec_alg_skcipher_setkey(tfm, key, keylen,
				       SEC_C_3DES_ECB_192_3KEY);
}