#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct crypto_skcipher {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tfms; } ;
struct crypt_config {unsigned int tfms_count; TYPE_1__ cipher_tfm; } ;
struct TYPE_5__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_6__ {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMDEBUG_LIMIT (char*,char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  any_tfm (struct crypt_config*) ; 
 int /*<<< orphan*/  crypt_free_tfms (struct crypt_config*) ; 
 int /*<<< orphan*/  crypto_alloc_skcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* crypto_skcipher_alg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypt_alloc_tfms_skcipher(struct crypt_config *cc, char *ciphermode)
{
	unsigned i;
	int err;

	cc->cipher_tfm.tfms = kcalloc(cc->tfms_count,
				      sizeof(struct crypto_skcipher *),
				      GFP_KERNEL);
	if (!cc->cipher_tfm.tfms)
		return -ENOMEM;

	for (i = 0; i < cc->tfms_count; i++) {
		cc->cipher_tfm.tfms[i] = crypto_alloc_skcipher(ciphermode, 0, 0);
		if (IS_ERR(cc->cipher_tfm.tfms[i])) {
			err = PTR_ERR(cc->cipher_tfm.tfms[i]);
			crypt_free_tfms(cc);
			return err;
		}
	}

	/*
	 * dm-crypt performance can vary greatly depending on which crypto
	 * algorithm implementation is used.  Help people debug performance
	 * problems by logging the ->cra_driver_name.
	 */
	DMDEBUG_LIMIT("%s using implementation \"%s\"", ciphermode,
	       crypto_skcipher_alg(any_tfm(cc))->base.cra_driver_name);
	return 0;
}