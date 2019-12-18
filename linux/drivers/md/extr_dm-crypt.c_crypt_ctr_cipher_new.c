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
struct dm_target {char* error; struct crypt_config* private; } ;
struct crypt_config {int tfms_count; int key_parts; int /*<<< orphan*/  iv_size; } ;

/* Variables and functions */
 int CRYPTO_MAX_ALG_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  any_tfm (struct crypt_config*) ; 
 int /*<<< orphan*/  any_tfm_aead (struct crypt_config*) ; 
 int crypt_alloc_tfms (struct crypt_config*,char*) ; 
 int crypt_ctr_auth_cipher (struct crypt_config*,char*) ; 
 scalar_t__ crypt_integrity_aead (struct crypt_config*) ; 
 int /*<<< orphan*/  crypto_aead_ivsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_ivsize (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int crypt_ctr_cipher_new(struct dm_target *ti, char *cipher_in, char *key,
				char **ivmode, char **ivopts)
{
	struct crypt_config *cc = ti->private;
	char *tmp, *cipher_api, buf[CRYPTO_MAX_ALG_NAME];
	int ret = -EINVAL;

	cc->tfms_count = 1;

	/*
	 * New format (capi: prefix)
	 * capi:cipher_api_spec-iv:ivopts
	 */
	tmp = &cipher_in[strlen("capi:")];

	/* Separate IV options if present, it can contain another '-' in hash name */
	*ivopts = strrchr(tmp, ':');
	if (*ivopts) {
		**ivopts = '\0';
		(*ivopts)++;
	}
	/* Parse IV mode */
	*ivmode = strrchr(tmp, '-');
	if (*ivmode) {
		**ivmode = '\0';
		(*ivmode)++;
	}
	/* The rest is crypto API spec */
	cipher_api = tmp;

	/* Alloc AEAD, can be used only in new format. */
	if (crypt_integrity_aead(cc)) {
		ret = crypt_ctr_auth_cipher(cc, cipher_api);
		if (ret < 0) {
			ti->error = "Invalid AEAD cipher spec";
			return -ENOMEM;
		}
	}

	if (*ivmode && !strcmp(*ivmode, "lmk"))
		cc->tfms_count = 64;

	if (*ivmode && !strcmp(*ivmode, "essiv")) {
		if (!*ivopts) {
			ti->error = "Digest algorithm missing for ESSIV mode";
			return -EINVAL;
		}
		ret = snprintf(buf, CRYPTO_MAX_ALG_NAME, "essiv(%s,%s)",
			       cipher_api, *ivopts);
		if (ret < 0 || ret >= CRYPTO_MAX_ALG_NAME) {
			ti->error = "Cannot allocate cipher string";
			return -ENOMEM;
		}
		cipher_api = buf;
	}

	cc->key_parts = cc->tfms_count;

	/* Allocate cipher */
	ret = crypt_alloc_tfms(cc, cipher_api);
	if (ret < 0) {
		ti->error = "Error allocating crypto tfm";
		return ret;
	}

	if (crypt_integrity_aead(cc))
		cc->iv_size = crypto_aead_ivsize(any_tfm_aead(cc));
	else
		cc->iv_size = crypto_skcipher_ivsize(any_tfm(cc));

	return 0;
}