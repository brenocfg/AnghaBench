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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int (* setkey ) (struct crypto_aead*,int /*<<< orphan*/  const*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_NEED_KEY ; 
 TYPE_1__* crypto_aead_alg (struct crypto_aead*) ; 
 unsigned long crypto_aead_alignmask (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_clear_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int setkey_unaligned (struct crypto_aead*,int /*<<< orphan*/  const*,unsigned int) ; 
 int stub1 (struct crypto_aead*,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

int crypto_aead_setkey(struct crypto_aead *tfm,
		       const u8 *key, unsigned int keylen)
{
	unsigned long alignmask = crypto_aead_alignmask(tfm);
	int err;

	if ((unsigned long)key & alignmask)
		err = setkey_unaligned(tfm, key, keylen);
	else
		err = crypto_aead_alg(tfm)->setkey(tfm, key, keylen);

	if (unlikely(err)) {
		crypto_aead_set_flags(tfm, CRYPTO_TFM_NEED_KEY);
		return err;
	}

	crypto_aead_clear_flags(tfm, CRYPTO_TFM_NEED_KEY);
	return 0;
}