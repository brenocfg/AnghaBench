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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct crypto_cipher {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (struct crypto_cipher*) ; 
 int PTR_ERR (struct crypto_cipher*) ; 
 int /*<<< orphan*/  crypto4xx_memcpy_to_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct crypto_cipher* crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crypto_cipher_setkey (struct crypto_cipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_free_cipher (struct crypto_cipher*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int crypto4xx_compute_gcm_hash_key_sw(__le32 *hash_start, const u8 *key,
					     unsigned int keylen)
{
	struct crypto_cipher *aes_tfm = NULL;
	uint8_t src[16] = { 0 };
	int rc = 0;

	aes_tfm = crypto_alloc_cipher("aes", 0, CRYPTO_ALG_ASYNC |
				      CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(aes_tfm)) {
		rc = PTR_ERR(aes_tfm);
		pr_warn("could not load aes cipher driver: %d\n", rc);
		return rc;
	}

	rc = crypto_cipher_setkey(aes_tfm, key, keylen);
	if (rc) {
		pr_err("setkey() failed: %d\n", rc);
		goto out;
	}

	crypto_cipher_encrypt_one(aes_tfm, src, src);
	crypto4xx_memcpy_to_le32(hash_start, src, 16);
out:
	crypto_free_cipher(aes_tfm);
	return rc;
}