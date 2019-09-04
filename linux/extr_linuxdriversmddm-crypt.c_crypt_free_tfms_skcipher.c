#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ ** tfms; } ;
struct crypt_config {unsigned int tfms_count; TYPE_1__ cipher_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void crypt_free_tfms_skcipher(struct crypt_config *cc)
{
	unsigned i;

	if (!cc->cipher_tfm.tfms)
		return;

	for (i = 0; i < cc->tfms_count; i++)
		if (cc->cipher_tfm.tfms[i] && !IS_ERR(cc->cipher_tfm.tfms[i])) {
			crypto_free_skcipher(cc->cipher_tfm.tfms[i]);
			cc->cipher_tfm.tfms[i] = NULL;
		}

	kfree(cc->cipher_tfm.tfms);
	cc->cipher_tfm.tfms = NULL;
}