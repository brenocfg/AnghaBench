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
struct crypto_alg {int /*<<< orphan*/  cra_module; } ;

/* Variables and functions */
 struct crypto_alg* crypto_alg_get (struct crypto_alg*) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

struct crypto_alg *crypto_mod_get(struct crypto_alg *alg)
{
	return try_module_get(alg->cra_module) ? crypto_alg_get(alg) : NULL;
}