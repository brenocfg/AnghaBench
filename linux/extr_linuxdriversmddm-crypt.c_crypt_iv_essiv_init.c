#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct iv_essiv_private {int /*<<< orphan*/  hash_tfm; int /*<<< orphan*/  salt; } ;
struct crypto_cipher {int dummy; } ;
struct TYPE_6__ {struct iv_essiv_private essiv; } ;
struct crypt_config {struct crypto_cipher* iv_private; int /*<<< orphan*/  key_size; int /*<<< orphan*/  key; TYPE_1__ iv_gen_private; } ;
struct TYPE_7__ {scalar_t__ flags; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int crypto_cipher_setkey (struct crypto_cipher*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_shash_digest (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_shash_digestsize (int /*<<< orphan*/ ) ; 
 TYPE_2__* desc ; 
 int /*<<< orphan*/  shash_desc_zero (TYPE_2__*) ; 

__attribute__((used)) static int crypt_iv_essiv_init(struct crypt_config *cc)
{
	struct iv_essiv_private *essiv = &cc->iv_gen_private.essiv;
	SHASH_DESC_ON_STACK(desc, essiv->hash_tfm);
	struct crypto_cipher *essiv_tfm;
	int err;

	desc->tfm = essiv->hash_tfm;
	desc->flags = 0;

	err = crypto_shash_digest(desc, cc->key, cc->key_size, essiv->salt);
	shash_desc_zero(desc);
	if (err)
		return err;

	essiv_tfm = cc->iv_private;

	err = crypto_cipher_setkey(essiv_tfm, essiv->salt,
			    crypto_shash_digestsize(essiv->hash_tfm));
	if (err)
		return err;

	return 0;
}