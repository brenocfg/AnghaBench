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
struct kobject {int dummy; } ;
struct bus_type {TYPE_1__* dev_root; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 struct bus_type* edac_get_sysfs_subsys () ; 
 int /*<<< orphan*/  edac_pci_sysfs_refcount ; 
 int /*<<< orphan*/  edac_pci_top_main_kobj ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int kobject_init_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktype_edac_pci_main_kobj ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edac_pci_main_kobj_setup(void)
{
	int err;
	struct bus_type *edac_subsys;

	edac_dbg(0, "\n");

	/* check and count if we have already created the main kobject */
	if (atomic_inc_return(&edac_pci_sysfs_refcount) != 1)
		return 0;

	/* First time, so create the main kobject and its
	 * controls and attributes
	 */
	edac_subsys = edac_get_sysfs_subsys();

	/* Bump the reference count on this module to ensure the
	 * modules isn't unloaded until we deconstruct the top
	 * level main kobj for EDAC PCI
	 */
	if (!try_module_get(THIS_MODULE)) {
		edac_dbg(1, "try_module_get() failed\n");
		err = -ENODEV;
		goto decrement_count_fail;
	}

	edac_pci_top_main_kobj = kzalloc(sizeof(struct kobject), GFP_KERNEL);
	if (!edac_pci_top_main_kobj) {
		edac_dbg(1, "Failed to allocate\n");
		err = -ENOMEM;
		goto kzalloc_fail;
	}

	/* Instanstiate the pci object */
	err = kobject_init_and_add(edac_pci_top_main_kobj,
				   &ktype_edac_pci_main_kobj,
				   &edac_subsys->dev_root->kobj, "pci");
	if (err) {
		edac_dbg(1, "Failed to register '.../edac/pci'\n");
		goto kobject_init_and_add_fail;
	}

	/* At this point, to 'release' the top level kobject
	 * for EDAC PCI, then edac_pci_main_kobj_teardown()
	 * must be used, for resources to be cleaned up properly
	 */
	kobject_uevent(edac_pci_top_main_kobj, KOBJ_ADD);
	edac_dbg(1, "Registered '.../edac/pci' kobject\n");

	return 0;

	/* Error unwind statck */
kobject_init_and_add_fail:
	kfree(edac_pci_top_main_kobj);

kzalloc_fail:
	module_put(THIS_MODULE);

decrement_count_fail:
	/* if are on this error exit, nothing to tear down */
	atomic_dec(&edac_pci_sysfs_refcount);

	return err;
}