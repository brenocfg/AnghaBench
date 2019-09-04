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
 int aes_set_key_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_tfm (struct crypto_skcipher*) ; 

__attribute__((used)) static int aesni_skcipher_setkey(struct crypto_skcipher *tfm, const u8 *key,
			         unsigned int len)
{
	return aes_set_key_common(crypto_skcipher_tfm(tfm),
				  crypto_skcipher_ctx(tfm), key, len);
}