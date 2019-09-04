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
struct simd_skcipher_alg {int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_skcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct simd_skcipher_alg*) ; 

void simd_skcipher_free(struct simd_skcipher_alg *salg)
{
	crypto_unregister_skcipher(&salg->alg);
	kfree(salg);
}