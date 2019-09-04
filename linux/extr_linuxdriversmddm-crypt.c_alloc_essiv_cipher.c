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
struct dm_target {char* error; } ;
struct crypto_cipher {int dummy; } ;
struct crypt_config {scalar_t__ iv_size; int /*<<< orphan*/  cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int EINVAL ; 
 struct crypto_cipher* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_cipher*) ; 
 struct crypto_cipher* crypto_alloc_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_cipher_blocksize (struct crypto_cipher*) ; 
 int crypto_cipher_setkey (struct crypto_cipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_free_cipher (struct crypto_cipher*) ; 

__attribute__((used)) static struct crypto_cipher *alloc_essiv_cipher(struct crypt_config *cc,
						struct dm_target *ti,
						const u8 *salt,
						unsigned int saltsize)
{
	struct crypto_cipher *essiv_tfm;
	int err;

	/* Setup the essiv_tfm with the given salt */
	essiv_tfm = crypto_alloc_cipher(cc->cipher, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(essiv_tfm)) {
		ti->error = "Error allocating crypto tfm for ESSIV";
		return essiv_tfm;
	}

	if (crypto_cipher_blocksize(essiv_tfm) != cc->iv_size) {
		ti->error = "Block size of ESSIV cipher does "
			    "not match IV size of block cipher";
		crypto_free_cipher(essiv_tfm);
		return ERR_PTR(-EINVAL);
	}

	err = crypto_cipher_setkey(essiv_tfm, salt, saltsize);
	if (err) {
		ti->error = "Failed to set key for ESSIV cipher";
		crypto_free_cipher(essiv_tfm);
		return ERR_PTR(err);
	}

	return essiv_tfm;
}