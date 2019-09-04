#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sahara_dev {scalar_t__ version; } ;
struct TYPE_9__ {int /*<<< orphan*/  cra_list; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ SAHARA_VERSION_3 ; 
 TYPE_1__* aes_algs ; 
 int crypto_register_ahash (TYPE_1__*) ; 
 int crypto_register_alg (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_unregister_alg (TYPE_1__*) ; 
 TYPE_1__* sha_v3_algs ; 
 TYPE_1__* sha_v4_algs ; 

__attribute__((used)) static int sahara_register_algs(struct sahara_dev *dev)
{
	int err;
	unsigned int i, j, k, l;

	for (i = 0; i < ARRAY_SIZE(aes_algs); i++) {
		INIT_LIST_HEAD(&aes_algs[i].cra_list);
		err = crypto_register_alg(&aes_algs[i]);
		if (err)
			goto err_aes_algs;
	}

	for (k = 0; k < ARRAY_SIZE(sha_v3_algs); k++) {
		err = crypto_register_ahash(&sha_v3_algs[k]);
		if (err)
			goto err_sha_v3_algs;
	}

	if (dev->version > SAHARA_VERSION_3)
		for (l = 0; l < ARRAY_SIZE(sha_v4_algs); l++) {
			err = crypto_register_ahash(&sha_v4_algs[l]);
			if (err)
				goto err_sha_v4_algs;
		}

	return 0;

err_sha_v4_algs:
	for (j = 0; j < l; j++)
		crypto_unregister_ahash(&sha_v4_algs[j]);

err_sha_v3_algs:
	for (j = 0; j < k; j++)
		crypto_unregister_ahash(&sha_v3_algs[j]);

err_aes_algs:
	for (j = 0; j < i; j++)
		crypto_unregister_alg(&aes_algs[j]);

	return err;
}