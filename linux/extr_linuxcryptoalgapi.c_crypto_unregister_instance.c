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
struct crypto_instance {int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alg_sem ; 
 int /*<<< orphan*/  crypto_remove_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_remove_instance (struct crypto_instance*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_remove_spawns (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int crypto_unregister_instance(struct crypto_instance *inst)
{
	LIST_HEAD(list);

	down_write(&crypto_alg_sem);

	crypto_remove_spawns(&inst->alg, &list, NULL);
	crypto_remove_instance(inst, &list);

	up_write(&crypto_alg_sem);

	crypto_remove_final(&list);

	return 0;
}