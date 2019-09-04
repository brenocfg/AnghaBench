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
struct crypt_config {scalar_t__ cipher; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  any_tfm (struct crypt_config*) ; 
 int /*<<< orphan*/  any_tfm_aead (struct crypt_config*) ; 
 scalar_t__ crypt_integrity_aead (struct crypt_config*) ; 
 scalar_t__ crypt_integrity_hmac (struct crypt_config*) ; 
 int /*<<< orphan*/  crypto_aead_tfm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_tfm (int /*<<< orphan*/ ) ; 
 char* crypto_tfm_alg_name (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrdup (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 void* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncpy (scalar_t__,char*,int) ; 

__attribute__((used)) static int crypt_ctr_blkdev_cipher(struct crypt_config *cc)
{
	const char *alg_name = NULL;
	char *start, *end;

	if (crypt_integrity_aead(cc)) {
		alg_name = crypto_tfm_alg_name(crypto_aead_tfm(any_tfm_aead(cc)));
		if (!alg_name)
			return -EINVAL;
		if (crypt_integrity_hmac(cc)) {
			alg_name = strchr(alg_name, ',');
			if (!alg_name)
				return -EINVAL;
		}
		alg_name++;
	} else {
		alg_name = crypto_tfm_alg_name(crypto_skcipher_tfm(any_tfm(cc)));
		if (!alg_name)
			return -EINVAL;
	}

	start = strchr(alg_name, '(');
	end = strchr(alg_name, ')');

	if (!start && !end) {
		cc->cipher = kstrdup(alg_name, GFP_KERNEL);
		return cc->cipher ? 0 : -ENOMEM;
	}

	if (!start || !end || ++start >= end)
		return -EINVAL;

	cc->cipher = kzalloc(end - start + 1, GFP_KERNEL);
	if (!cc->cipher)
		return -ENOMEM;

	strncpy(cc->cipher, start, end - start);

	return 0;
}