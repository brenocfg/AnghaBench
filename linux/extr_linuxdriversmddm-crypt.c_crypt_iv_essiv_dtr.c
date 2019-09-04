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
struct iv_essiv_private {int /*<<< orphan*/ * salt; int /*<<< orphan*/ * hash_tfm; } ;
struct crypto_cipher {int dummy; } ;
struct TYPE_2__ {struct iv_essiv_private essiv; } ;
struct crypt_config {struct crypto_cipher* iv_private; TYPE_1__ iv_gen_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_cipher (struct crypto_cipher*) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypt_iv_essiv_dtr(struct crypt_config *cc)
{
	struct crypto_cipher *essiv_tfm;
	struct iv_essiv_private *essiv = &cc->iv_gen_private.essiv;

	crypto_free_shash(essiv->hash_tfm);
	essiv->hash_tfm = NULL;

	kzfree(essiv->salt);
	essiv->salt = NULL;

	essiv_tfm = cc->iv_private;

	if (essiv_tfm)
		crypto_free_cipher(essiv_tfm);

	cc->iv_private = NULL;
}