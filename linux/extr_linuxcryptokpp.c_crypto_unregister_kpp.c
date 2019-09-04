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
struct kpp_alg {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 

void crypto_unregister_kpp(struct kpp_alg *alg)
{
	crypto_unregister_alg(&alg->base);
}