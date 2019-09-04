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
struct TYPE_2__ {scalar_t__ has_hmac; scalar_t__ has_sha_384_512; scalar_t__ has_sha224; } ;
struct atmel_sha_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int crypto_register_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sha_1_256_algs ; 
 int /*<<< orphan*/  sha_224_alg ; 
 int /*<<< orphan*/ * sha_384_512_algs ; 
 int /*<<< orphan*/ * sha_hmac_algs ; 

__attribute__((used)) static int atmel_sha_register_algs(struct atmel_sha_dev *dd)
{
	int err, i, j;

	for (i = 0; i < ARRAY_SIZE(sha_1_256_algs); i++) {
		err = crypto_register_ahash(&sha_1_256_algs[i]);
		if (err)
			goto err_sha_1_256_algs;
	}

	if (dd->caps.has_sha224) {
		err = crypto_register_ahash(&sha_224_alg);
		if (err)
			goto err_sha_224_algs;
	}

	if (dd->caps.has_sha_384_512) {
		for (i = 0; i < ARRAY_SIZE(sha_384_512_algs); i++) {
			err = crypto_register_ahash(&sha_384_512_algs[i]);
			if (err)
				goto err_sha_384_512_algs;
		}
	}

	if (dd->caps.has_hmac) {
		for (i = 0; i < ARRAY_SIZE(sha_hmac_algs); i++) {
			err = crypto_register_ahash(&sha_hmac_algs[i]);
			if (err)
				goto err_sha_hmac_algs;
		}
	}

	return 0;

	/*i = ARRAY_SIZE(sha_hmac_algs);*/
err_sha_hmac_algs:
	for (j = 0; j < i; j++)
		crypto_unregister_ahash(&sha_hmac_algs[j]);
	i = ARRAY_SIZE(sha_384_512_algs);
err_sha_384_512_algs:
	for (j = 0; j < i; j++)
		crypto_unregister_ahash(&sha_384_512_algs[j]);
	crypto_unregister_ahash(&sha_224_alg);
err_sha_224_algs:
	i = ARRAY_SIZE(sha_1_256_algs);
err_sha_1_256_algs:
	for (j = 0; j < i; j++)
		crypto_unregister_ahash(&sha_1_256_algs[j]);

	return err;
}