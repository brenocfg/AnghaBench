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
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_alloc_skcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_skcipher* crypto_default_null_skcipher ; 
 int /*<<< orphan*/  crypto_default_null_skcipher_lock ; 
 int /*<<< orphan*/  crypto_default_null_skcipher_refcnt ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct crypto_skcipher *crypto_get_default_null_skcipher(void)
{
	struct crypto_skcipher *tfm;

	mutex_lock(&crypto_default_null_skcipher_lock);
	tfm = crypto_default_null_skcipher;

	if (!tfm) {
		tfm = crypto_alloc_skcipher("ecb(cipher_null)",
					    0, CRYPTO_ALG_ASYNC);
		if (IS_ERR(tfm))
			goto unlock;

		crypto_default_null_skcipher = tfm;
	}

	crypto_default_null_skcipher_refcnt++;

unlock:
	mutex_unlock(&crypto_default_null_skcipher_lock);

	return tfm;
}