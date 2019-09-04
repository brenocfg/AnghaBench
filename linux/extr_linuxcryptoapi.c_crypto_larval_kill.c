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
struct crypto_larval {int /*<<< orphan*/  completion; } ;
struct crypto_alg {int /*<<< orphan*/  cra_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_alg_put (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_alg_sem ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void crypto_larval_kill(struct crypto_alg *alg)
{
	struct crypto_larval *larval = (void *)alg;

	down_write(&crypto_alg_sem);
	list_del(&alg->cra_list);
	up_write(&crypto_alg_sem);
	complete_all(&larval->completion);
	crypto_alg_put(alg);
}