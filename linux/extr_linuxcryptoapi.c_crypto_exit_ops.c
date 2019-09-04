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
struct crypto_type {int dummy; } ;
struct crypto_tfm {int /*<<< orphan*/  (* exit ) (struct crypto_tfm*) ;TYPE_1__* __crt_alg; } ;
struct TYPE_2__ {struct crypto_type* cra_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct crypto_tfm*) ; 

__attribute__((used)) static void crypto_exit_ops(struct crypto_tfm *tfm)
{
	const struct crypto_type *type = tfm->__crt_alg->cra_type;

	if (type && tfm->exit)
		tfm->exit(tfm);
}