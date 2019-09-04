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
struct mv_cesa_dev {TYPE_1__* caps; } ;
struct TYPE_2__ {int ncipher_algs; int nahash_algs; int /*<<< orphan*/ * cipher_algs; int /*<<< orphan*/ * ahash_algs; } ;

/* Variables and functions */
 int crypto_register_ahash (int /*<<< orphan*/ ) ; 
 int crypto_register_skcipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_skcipher (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_cesa_add_algs(struct mv_cesa_dev *cesa)
{
	int ret;
	int i, j;

	for (i = 0; i < cesa->caps->ncipher_algs; i++) {
		ret = crypto_register_skcipher(cesa->caps->cipher_algs[i]);
		if (ret)
			goto err_unregister_crypto;
	}

	for (i = 0; i < cesa->caps->nahash_algs; i++) {
		ret = crypto_register_ahash(cesa->caps->ahash_algs[i]);
		if (ret)
			goto err_unregister_ahash;
	}

	return 0;

err_unregister_ahash:
	for (j = 0; j < i; j++)
		crypto_unregister_ahash(cesa->caps->ahash_algs[j]);
	i = cesa->caps->ncipher_algs;

err_unregister_crypto:
	for (j = 0; j < i; j++)
		crypto_unregister_skcipher(cesa->caps->cipher_algs[j]);

	return ret;
}