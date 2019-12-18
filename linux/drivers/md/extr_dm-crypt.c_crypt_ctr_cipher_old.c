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
struct crypt_config {int tfms_count; int key_parts; } ;

/* Variables and functions */
 int CRYPTO_MAX_ALG_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int crypt_alloc_tfms (struct crypt_config*,char*) ; 
 scalar_t__ crypt_integrity_aead (struct crypt_config*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,char*,...) ; 
 int sscanf (char*,char*,int*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int crypt_ctr_cipher_old(struct dm_target *ti, char *cipher_in, char *key,
				char **ivmode, char **ivopts)
{
	struct crypt_config *cc = ti->private;
	char *tmp, *cipher, *chainmode, *keycount;
	char *cipher_api = NULL;
	int ret = -EINVAL;
	char dummy;

	if (strchr(cipher_in, '(') || crypt_integrity_aead(cc)) {
		ti->error = "Bad cipher specification";
		return -EINVAL;
	}

	/*
	 * Legacy dm-crypt cipher specification
	 * cipher[:keycount]-mode-iv:ivopts
	 */
	tmp = cipher_in;
	keycount = strsep(&tmp, "-");
	cipher = strsep(&keycount, ":");

	if (!keycount)
		cc->tfms_count = 1;
	else if (sscanf(keycount, "%u%c", &cc->tfms_count, &dummy) != 1 ||
		 !is_power_of_2(cc->tfms_count)) {
		ti->error = "Bad cipher key count specification";
		return -EINVAL;
	}
	cc->key_parts = cc->tfms_count;

	chainmode = strsep(&tmp, "-");
	*ivmode = strsep(&tmp, ":");
	*ivopts = tmp;

	/*
	 * For compatibility with the original dm-crypt mapping format, if
	 * only the cipher name is supplied, use cbc-plain.
	 */
	if (!chainmode || (!strcmp(chainmode, "plain") && !*ivmode)) {
		chainmode = "cbc";
		*ivmode = "plain";
	}

	if (strcmp(chainmode, "ecb") && !*ivmode) {
		ti->error = "IV mechanism required";
		return -EINVAL;
	}

	cipher_api = kmalloc(CRYPTO_MAX_ALG_NAME, GFP_KERNEL);
	if (!cipher_api)
		goto bad_mem;

	if (*ivmode && !strcmp(*ivmode, "essiv")) {
		if (!*ivopts) {
			ti->error = "Digest algorithm missing for ESSIV mode";
			kfree(cipher_api);
			return -EINVAL;
		}
		ret = snprintf(cipher_api, CRYPTO_MAX_ALG_NAME,
			       "essiv(%s(%s),%s)", chainmode, cipher, *ivopts);
	} else {
		ret = snprintf(cipher_api, CRYPTO_MAX_ALG_NAME,
			       "%s(%s)", chainmode, cipher);
	}
	if (ret < 0 || ret >= CRYPTO_MAX_ALG_NAME) {
		kfree(cipher_api);
		goto bad_mem;
	}

	/* Allocate cipher */
	ret = crypt_alloc_tfms(cc, cipher_api);
	if (ret < 0) {
		ti->error = "Error allocating crypto tfm";
		kfree(cipher_api);
		return ret;
	}
	kfree(cipher_api);

	return 0;
bad_mem:
	ti->error = "Cannot allocate cipher strings";
	return -ENOMEM;
}