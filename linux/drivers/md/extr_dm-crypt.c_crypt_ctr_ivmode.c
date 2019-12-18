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
typedef  int /*<<< orphan*/  u64 ;
struct dm_target {char* error; struct crypt_config* private; } ;
struct crypt_config {int iv_size; int key_size; int key_parts; int key_extra_size; int integrity_iv_size; int /*<<< orphan*/ * iv_gen_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int EINVAL ; 
 int TCW_WHITENING_SIZE ; 
 int /*<<< orphan*/  any_tfm (struct crypt_config*) ; 
 int /*<<< orphan*/  any_tfm_aead (struct crypt_config*) ; 
 scalar_t__ crypt_integrity_aead (struct crypt_config*) ; 
 int /*<<< orphan*/  crypt_iv_benbi_ops ; 
 int /*<<< orphan*/  crypt_iv_eboiv_ops ; 
 int /*<<< orphan*/  crypt_iv_essiv_ops ; 
 int /*<<< orphan*/  crypt_iv_lmk_ops ; 
 int /*<<< orphan*/  crypt_iv_null_ops ; 
 int /*<<< orphan*/  crypt_iv_plain64_ops ; 
 int /*<<< orphan*/  crypt_iv_plain64be_ops ; 
 int /*<<< orphan*/  crypt_iv_plain_ops ; 
 int /*<<< orphan*/  crypt_iv_random_ops ; 
 int /*<<< orphan*/  crypt_iv_tcw_ops ; 
 int crypto_aead_ivsize (int /*<<< orphan*/ ) ; 
 int crypto_skcipher_ivsize (int /*<<< orphan*/ ) ; 
 int max (int,unsigned int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int crypt_ctr_ivmode(struct dm_target *ti, const char *ivmode)
{
	struct crypt_config *cc = ti->private;

	if (crypt_integrity_aead(cc))
		cc->iv_size = crypto_aead_ivsize(any_tfm_aead(cc));
	else
		cc->iv_size = crypto_skcipher_ivsize(any_tfm(cc));

	if (cc->iv_size)
		/* at least a 64 bit sector number should fit in our buffer */
		cc->iv_size = max(cc->iv_size,
				  (unsigned int)(sizeof(u64) / sizeof(u8)));
	else if (ivmode) {
		DMWARN("Selected cipher does not support IVs");
		ivmode = NULL;
	}

	/* Choose ivmode, see comments at iv code. */
	if (ivmode == NULL)
		cc->iv_gen_ops = NULL;
	else if (strcmp(ivmode, "plain") == 0)
		cc->iv_gen_ops = &crypt_iv_plain_ops;
	else if (strcmp(ivmode, "plain64") == 0)
		cc->iv_gen_ops = &crypt_iv_plain64_ops;
	else if (strcmp(ivmode, "plain64be") == 0)
		cc->iv_gen_ops = &crypt_iv_plain64be_ops;
	else if (strcmp(ivmode, "essiv") == 0)
		cc->iv_gen_ops = &crypt_iv_essiv_ops;
	else if (strcmp(ivmode, "benbi") == 0)
		cc->iv_gen_ops = &crypt_iv_benbi_ops;
	else if (strcmp(ivmode, "null") == 0)
		cc->iv_gen_ops = &crypt_iv_null_ops;
	else if (strcmp(ivmode, "eboiv") == 0)
		cc->iv_gen_ops = &crypt_iv_eboiv_ops;
	else if (strcmp(ivmode, "lmk") == 0) {
		cc->iv_gen_ops = &crypt_iv_lmk_ops;
		/*
		 * Version 2 and 3 is recognised according
		 * to length of provided multi-key string.
		 * If present (version 3), last key is used as IV seed.
		 * All keys (including IV seed) are always the same size.
		 */
		if (cc->key_size % cc->key_parts) {
			cc->key_parts++;
			cc->key_extra_size = cc->key_size / cc->key_parts;
		}
	} else if (strcmp(ivmode, "tcw") == 0) {
		cc->iv_gen_ops = &crypt_iv_tcw_ops;
		cc->key_parts += 2; /* IV + whitening */
		cc->key_extra_size = cc->iv_size + TCW_WHITENING_SIZE;
	} else if (strcmp(ivmode, "random") == 0) {
		cc->iv_gen_ops = &crypt_iv_random_ops;
		/* Need storage space in integrity fields. */
		cc->integrity_iv_size = cc->iv_size;
	} else {
		ti->error = "Invalid IV mode";
		return -EINVAL;
	}

	return 0;
}