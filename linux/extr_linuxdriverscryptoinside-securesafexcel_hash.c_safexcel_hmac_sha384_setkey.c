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
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_DIGEST_SIZE ; 
 int safexcel_hmac_alg_setkey (struct crypto_ahash*,int /*<<< orphan*/  const*,unsigned int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int safexcel_hmac_sha384_setkey(struct crypto_ahash *tfm, const u8 *key,
				       unsigned int keylen)
{
	return safexcel_hmac_alg_setkey(tfm, key, keylen, "safexcel-sha384",
					SHA512_DIGEST_SIZE);
}