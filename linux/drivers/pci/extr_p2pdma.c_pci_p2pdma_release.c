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
struct pci_p2pdma {int /*<<< orphan*/  map_types; int /*<<< orphan*/  pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {TYPE_1__ dev; struct pci_p2pdma* p2pdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2pmem_group ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_p2pdma_release(void *data)
{
	struct pci_dev *pdev = data;
	struct pci_p2pdma *p2pdma = pdev->p2pdma;

	if (!p2pdma)
		return;

	/* Flush and disable pci_alloc_p2p_mem() */
	pdev->p2pdma = NULL;
	synchronize_rcu();

	gen_pool_destroy(p2pdma->pool);
	sysfs_remove_group(&pdev->dev.kobj, &p2pmem_group);
	xa_destroy(&p2pdma->map_types);
}