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
struct tce_iommu_prereg {int /*<<< orphan*/  next; int /*<<< orphan*/  mem; } ;
struct tce_container {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tce_iommu_prereg*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 long mm_iommu_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long tce_iommu_prereg_free(struct tce_container *container,
		struct tce_iommu_prereg *tcemem)
{
	long ret;

	ret = mm_iommu_put(container->mm, tcemem->mem);
	if (ret)
		return ret;

	list_del(&tcemem->next);
	kfree(tcemem);

	return 0;
}