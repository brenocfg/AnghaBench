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
struct iv_lmk_private {int /*<<< orphan*/ * seed; int /*<<< orphan*/ * hash_tfm; } ;
struct TYPE_2__ {struct iv_lmk_private lmk; } ;
struct crypt_config {TYPE_1__ iv_gen_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypt_iv_lmk_dtr(struct crypt_config *cc)
{
	struct iv_lmk_private *lmk = &cc->iv_gen_private.lmk;

	if (lmk->hash_tfm && !IS_ERR(lmk->hash_tfm))
		crypto_free_shash(lmk->hash_tfm);
	lmk->hash_tfm = NULL;

	kzfree(lmk->seed);
	lmk->seed = NULL;
}