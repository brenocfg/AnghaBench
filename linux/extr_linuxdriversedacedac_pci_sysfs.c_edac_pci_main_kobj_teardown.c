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
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_pci_sysfs_refcount ; 
 int /*<<< orphan*/  edac_pci_top_main_kobj ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edac_pci_main_kobj_teardown(void)
{
	edac_dbg(0, "\n");

	/* Decrement the count and only if no more controller instances
	 * are connected perform the unregisteration of the top level
	 * main kobj
	 */
	if (atomic_dec_return(&edac_pci_sysfs_refcount) == 0) {
		edac_dbg(0, "called kobject_put on main kobj\n");
		kobject_put(edac_pci_top_main_kobj);
	}
}