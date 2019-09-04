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
struct padata_pcrypt {int /*<<< orphan*/  pinst; int /*<<< orphan*/  wq; int /*<<< orphan*/  nblock; TYPE_1__* cb_cpumask; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  padata_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padata_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padata_unregister_cpumask_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcrypt_fini_padata(struct padata_pcrypt *pcrypt)
{
	free_cpumask_var(pcrypt->cb_cpumask->mask);
	kfree(pcrypt->cb_cpumask);

	padata_stop(pcrypt->pinst);
	padata_unregister_cpumask_notifier(pcrypt->pinst, &pcrypt->nblock);
	destroy_workqueue(pcrypt->wq);
	padata_free(pcrypt->pinst);
}