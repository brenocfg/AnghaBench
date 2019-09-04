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

/* Variables and functions */
 int ENOMEM ; 
 int arch_gnttab_valloc (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  arch_gnttab_vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_shared_vm_area ; 
 int /*<<< orphan*/  gnttab_status_vm_area ; 
 int /*<<< orphan*/  xen_pv_domain () ; 

int arch_gnttab_init(unsigned long nr_shared, unsigned long nr_status)
{
	int ret;

	if (!xen_pv_domain())
		return 0;

	ret = arch_gnttab_valloc(&gnttab_shared_vm_area, nr_shared);
	if (ret < 0)
		return ret;

	/*
	 * Always allocate the space for the status frames in case
	 * we're migrated to a host with V2 support.
	 */
	ret = arch_gnttab_valloc(&gnttab_status_vm_area, nr_status);
	if (ret < 0)
		goto err;

	return 0;
err:
	arch_gnttab_vfree(&gnttab_shared_vm_area);
	return -ENOMEM;
}