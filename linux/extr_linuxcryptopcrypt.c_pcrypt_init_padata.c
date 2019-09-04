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
struct pcrypt_cpumask {int /*<<< orphan*/  mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  notifier_call; } ;
struct padata_pcrypt {int /*<<< orphan*/  wq; int /*<<< orphan*/  pinst; TYPE_1__ nblock; int /*<<< orphan*/  cb_cpumask; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WQ_CPU_INTENSIVE ; 
 int WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int,char const*) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  kfree (struct pcrypt_cpumask*) ; 
 struct pcrypt_cpumask* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padata_alloc_possible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padata_free (int /*<<< orphan*/ ) ; 
 int padata_register_cpumask_notifier (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  padata_unregister_cpumask_notifier (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pcrypt_cpumask_change_notify ; 
 int pcrypt_sysfs_add (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct pcrypt_cpumask*) ; 

__attribute__((used)) static int pcrypt_init_padata(struct padata_pcrypt *pcrypt,
			      const char *name)
{
	int ret = -ENOMEM;
	struct pcrypt_cpumask *mask;

	get_online_cpus();

	pcrypt->wq = alloc_workqueue("%s", WQ_MEM_RECLAIM | WQ_CPU_INTENSIVE,
				     1, name);
	if (!pcrypt->wq)
		goto err;

	pcrypt->pinst = padata_alloc_possible(pcrypt->wq);
	if (!pcrypt->pinst)
		goto err_destroy_workqueue;

	mask = kmalloc(sizeof(*mask), GFP_KERNEL);
	if (!mask)
		goto err_free_padata;
	if (!alloc_cpumask_var(&mask->mask, GFP_KERNEL)) {
		kfree(mask);
		goto err_free_padata;
	}

	cpumask_and(mask->mask, cpu_possible_mask, cpu_online_mask);
	rcu_assign_pointer(pcrypt->cb_cpumask, mask);

	pcrypt->nblock.notifier_call = pcrypt_cpumask_change_notify;
	ret = padata_register_cpumask_notifier(pcrypt->pinst, &pcrypt->nblock);
	if (ret)
		goto err_free_cpumask;

	ret = pcrypt_sysfs_add(pcrypt->pinst, name);
	if (ret)
		goto err_unregister_notifier;

	put_online_cpus();

	return ret;

err_unregister_notifier:
	padata_unregister_cpumask_notifier(pcrypt->pinst, &pcrypt->nblock);
err_free_cpumask:
	free_cpumask_var(mask->mask);
	kfree(mask);
err_free_padata:
	padata_free(pcrypt->pinst);
err_destroy_workqueue:
	destroy_workqueue(pcrypt->wq);
err:
	put_online_cpus();

	return ret;
}