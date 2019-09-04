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
struct crypto_akcipher {int dummy; } ;

/* Variables and functions */
 int qat_rsa_setkey (struct crypto_akcipher*,void const*,unsigned int,int) ; 

__attribute__((used)) static int qat_rsa_setpubkey(struct crypto_akcipher *tfm, const void *key,
			     unsigned int keylen)
{
	return qat_rsa_setkey(tfm, key, keylen, false);
}