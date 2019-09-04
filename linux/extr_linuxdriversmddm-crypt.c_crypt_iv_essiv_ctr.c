#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dm_target {char* error; } ;
struct crypto_shash {int dummy; } ;
typedef  struct crypto_shash crypto_cipher ;
struct TYPE_3__ {struct crypto_shash* hash_tfm; int /*<<< orphan*/ * salt; } ;
struct TYPE_4__ {TYPE_1__ essiv; } ;
struct crypt_config {struct crypto_shash* iv_private; TYPE_2__ iv_gen_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 struct crypto_shash* alloc_essiv_cipher (struct crypt_config*,struct dm_target*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypt_iv_essiv_dtr (struct crypt_config*) ; 
 struct crypto_shash* crypto_alloc_shash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_shash_digestsize (struct crypto_shash*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypt_iv_essiv_ctr(struct crypt_config *cc, struct dm_target *ti,
			      const char *opts)
{
	struct crypto_cipher *essiv_tfm = NULL;
	struct crypto_shash *hash_tfm = NULL;
	u8 *salt = NULL;
	int err;

	if (!opts) {
		ti->error = "Digest algorithm missing for ESSIV mode";
		return -EINVAL;
	}

	/* Allocate hash algorithm */
	hash_tfm = crypto_alloc_shash(opts, 0, 0);
	if (IS_ERR(hash_tfm)) {
		ti->error = "Error initializing ESSIV hash";
		err = PTR_ERR(hash_tfm);
		goto bad;
	}

	salt = kzalloc(crypto_shash_digestsize(hash_tfm), GFP_KERNEL);
	if (!salt) {
		ti->error = "Error kmallocing salt storage in ESSIV";
		err = -ENOMEM;
		goto bad;
	}

	cc->iv_gen_private.essiv.salt = salt;
	cc->iv_gen_private.essiv.hash_tfm = hash_tfm;

	essiv_tfm = alloc_essiv_cipher(cc, ti, salt,
				       crypto_shash_digestsize(hash_tfm));
	if (IS_ERR(essiv_tfm)) {
		crypt_iv_essiv_dtr(cc);
		return PTR_ERR(essiv_tfm);
	}
	cc->iv_private = essiv_tfm;

	return 0;

bad:
	if (hash_tfm && !IS_ERR(hash_tfm))
		crypto_free_shash(hash_tfm);
	kfree(salt);
	return err;
}