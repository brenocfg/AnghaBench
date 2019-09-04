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
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  free_prng_context (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cprng_exit(struct crypto_tfm *tfm)
{
	free_prng_context(crypto_tfm_ctx(tfm));
}