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
struct percpu_ref {int dummy; } ;
struct pci_dev {TYPE_1__* p2pdma; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free_owner (int /*<<< orphan*/ ,uintptr_t,size_t,void**) ; 
 int /*<<< orphan*/  percpu_ref_put (struct percpu_ref*) ; 

void pci_free_p2pmem(struct pci_dev *pdev, void *addr, size_t size)
{
	struct percpu_ref *ref;

	gen_pool_free_owner(pdev->p2pdma->pool, (uintptr_t)addr, size,
			(void **) &ref);
	percpu_ref_put(ref);
}