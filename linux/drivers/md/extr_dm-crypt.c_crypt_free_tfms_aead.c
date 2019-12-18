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
struct TYPE_2__ {int /*<<< orphan*/ ** tfms_aead; } ;
struct crypt_config {TYPE_1__ cipher_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void crypt_free_tfms_aead(struct crypt_config *cc)
{
	if (!cc->cipher_tfm.tfms_aead)
		return;

	if (cc->cipher_tfm.tfms_aead[0] && !IS_ERR(cc->cipher_tfm.tfms_aead[0])) {
		crypto_free_aead(cc->cipher_tfm.tfms_aead[0]);
		cc->cipher_tfm.tfms_aead[0] = NULL;
	}

	kfree(cc->cipher_tfm.tfms_aead);
	cc->cipher_tfm.tfms_aead = NULL;
}