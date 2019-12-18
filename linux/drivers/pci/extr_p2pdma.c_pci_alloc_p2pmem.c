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
 scalar_t__ gen_pool_alloc_owner (int /*<<< orphan*/ ,size_t,void**) ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,size_t) ; 
 int /*<<< orphan*/  percpu_ref_tryget_live (struct percpu_ref*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

void *pci_alloc_p2pmem(struct pci_dev *pdev, size_t size)
{
	void *ret = NULL;
	struct percpu_ref *ref;

	/*
	 * Pairs with synchronize_rcu() in pci_p2pdma_release() to
	 * ensure pdev->p2pdma is non-NULL for the duration of the
	 * read-lock.
	 */
	rcu_read_lock();
	if (unlikely(!pdev->p2pdma))
		goto out;

	ret = (void *)gen_pool_alloc_owner(pdev->p2pdma->pool, size,
			(void **) &ref);
	if (!ret)
		goto out;

	if (unlikely(!percpu_ref_tryget_live(ref))) {
		gen_pool_free(pdev->p2pdma->pool, (unsigned long) ret, size);
		ret = NULL;
		goto out;
	}
out:
	rcu_read_unlock();
	return ret;
}