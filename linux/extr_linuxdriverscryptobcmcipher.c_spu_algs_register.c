#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  aead; int /*<<< orphan*/  hash; int /*<<< orphan*/  crypto; } ;
struct TYPE_8__ {int type; int registered; TYPE_1__ alg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
#define  CRYPTO_ALG_TYPE_ABLKCIPHER 130 
#define  CRYPTO_ALG_TYPE_AEAD 129 
#define  CRYPTO_ALG_TYPE_AHASH 128 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_unregister_aead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 TYPE_2__* driver_algs ; 
 int spu_register_ablkcipher (TYPE_2__*) ; 
 int spu_register_aead (TYPE_2__*) ; 
 int spu_register_ahash (TYPE_2__*) ; 

__attribute__((used)) static int spu_algs_register(struct device *dev)
{
	int i, j;
	int err;

	for (i = 0; i < ARRAY_SIZE(driver_algs); i++) {
		switch (driver_algs[i].type) {
		case CRYPTO_ALG_TYPE_ABLKCIPHER:
			err = spu_register_ablkcipher(&driver_algs[i]);
			break;
		case CRYPTO_ALG_TYPE_AHASH:
			err = spu_register_ahash(&driver_algs[i]);
			break;
		case CRYPTO_ALG_TYPE_AEAD:
			err = spu_register_aead(&driver_algs[i]);
			break;
		default:
			dev_err(dev,
				"iproc-crypto: unknown alg type: %d",
				driver_algs[i].type);
			err = -EINVAL;
		}

		if (err) {
			dev_err(dev, "alg registration failed with error %d\n",
				err);
			goto err_algs;
		}
	}

	return 0;

err_algs:
	for (j = 0; j < i; j++) {
		/* Skip any algorithm not registered */
		if (!driver_algs[j].registered)
			continue;
		switch (driver_algs[j].type) {
		case CRYPTO_ALG_TYPE_ABLKCIPHER:
			crypto_unregister_alg(&driver_algs[j].alg.crypto);
			driver_algs[j].registered = false;
			break;
		case CRYPTO_ALG_TYPE_AHASH:
			crypto_unregister_ahash(&driver_algs[j].alg.hash);
			driver_algs[j].registered = false;
			break;
		case CRYPTO_ALG_TYPE_AEAD:
			crypto_unregister_aead(&driver_algs[j].alg.aead);
			driver_algs[j].registered = false;
			break;
		}
	}
	return err;
}