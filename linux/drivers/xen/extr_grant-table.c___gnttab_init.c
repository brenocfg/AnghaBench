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
 int ENODEV ; 
 int gnttab_init () ; 
 int /*<<< orphan*/  xen_domain () ; 
 scalar_t__ xen_hvm_domain () ; 
 int /*<<< orphan*/  xen_pvh_domain () ; 

__attribute__((used)) static int __gnttab_init(void)
{
	if (!xen_domain())
		return -ENODEV;

	/* Delay grant-table initialization in the PV on HVM case */
	if (xen_hvm_domain() && !xen_pvh_domain())
		return 0;

	return gnttab_init();
}