#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mxc_scc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  alg; struct mxc_scc* scc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__**) ; 
 int crypto_register_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 TYPE_1__** scc_crypto_algs ; 

__attribute__((used)) static int mxc_scc_crypto_register(struct mxc_scc *scc)
{
	int i;
	int err = 0;

	for (i = 0; i < ARRAY_SIZE(scc_crypto_algs); i++) {
		scc_crypto_algs[i]->scc = scc;
		err = crypto_register_alg(&scc_crypto_algs[i]->alg);
		if (err)
			goto err_out;
	}

	return 0;

err_out:
	while (--i >= 0)
		crypto_unregister_alg(&scc_crypto_algs[i]->alg);

	return err;
}