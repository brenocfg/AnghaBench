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
struct skcipher_alg {int dummy; } ;
struct simd_skcipher_alg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_skciphers (struct skcipher_alg*,int) ; 
 int /*<<< orphan*/  simd_skcipher_free (struct simd_skcipher_alg*) ; 

void simd_unregister_skciphers(struct skcipher_alg *algs, int count,
			       struct simd_skcipher_alg **simd_algs)
{
	int i;

	crypto_unregister_skciphers(algs, count);

	for (i = 0; i < count; i++) {
		if (simd_algs[i]) {
			simd_skcipher_free(simd_algs[i]);
			simd_algs[i] = NULL;
		}
	}
}