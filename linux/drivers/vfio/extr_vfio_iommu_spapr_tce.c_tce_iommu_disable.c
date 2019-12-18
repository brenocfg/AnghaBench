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
struct tce_container {int enabled; int /*<<< orphan*/  locked_pages; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  account_locked_vm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tce_iommu_disable(struct tce_container *container)
{
	if (!container->enabled)
		return;

	container->enabled = false;

	BUG_ON(!container->mm);
	account_locked_vm(container->mm, container->locked_pages, false);
}