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
typedef  enum sec_cipher_alg { ____Placeholder_sec_cipher_alg } sec_cipher_alg ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int EINVAL ; 
 int SEC_C_AES_CBC_128 ; 
 int SEC_C_AES_CBC_192 ; 
 int SEC_C_AES_CBC_256 ; 
 int sec_alg_skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int,int) ; 

__attribute__((used)) static int sec_alg_skcipher_setkey_aes_cbc(struct crypto_skcipher *tfm,
					   const u8 *key, unsigned int keylen)
{
	enum sec_cipher_alg alg;

	switch (keylen) {
	case AES_KEYSIZE_128:
		alg = SEC_C_AES_CBC_128;
		break;
	case AES_KEYSIZE_192:
		alg = SEC_C_AES_CBC_192;
		break;
	case AES_KEYSIZE_256:
		alg = SEC_C_AES_CBC_256;
		break;
	default:
		return -EINVAL;
	}

	return sec_alg_skcipher_setkey(tfm, key, keylen, alg);
}