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
struct TYPE_3__ {int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__**) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 TYPE_1__** scc_crypto_algs ; 

__attribute__((used)) static void mxc_scc_crypto_unregister(void)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(scc_crypto_algs); i++)
		crypto_unregister_alg(&scc_crypto_algs[i]->alg);
}