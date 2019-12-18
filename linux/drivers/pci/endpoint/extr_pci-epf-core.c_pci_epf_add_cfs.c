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
struct pci_epf_driver {int /*<<< orphan*/  epf_group; struct pci_epf_device_id* id_table; } ;
struct pci_epf_device_id {scalar_t__* name; } ;
struct config_group {int /*<<< orphan*/  group_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_ENDPOINT_CONFIGFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct config_group*) ; 
 int PTR_ERR (struct config_group*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct config_group* pci_ep_cfs_add_epf_group (scalar_t__*) ; 
 int /*<<< orphan*/  pci_epf_mutex ; 
 int /*<<< orphan*/  pci_epf_remove_cfs (struct pci_epf_driver*) ; 

__attribute__((used)) static int pci_epf_add_cfs(struct pci_epf_driver *driver)
{
	struct config_group *group;
	const struct pci_epf_device_id *id;

	if (!IS_ENABLED(CONFIG_PCI_ENDPOINT_CONFIGFS))
		return 0;

	INIT_LIST_HEAD(&driver->epf_group);

	id = driver->id_table;
	while (id->name[0]) {
		group = pci_ep_cfs_add_epf_group(id->name);
		if (IS_ERR(group)) {
			pci_epf_remove_cfs(driver);
			return PTR_ERR(group);
		}

		mutex_lock(&pci_epf_mutex);
		list_add_tail(&group->group_entry, &driver->epf_group);
		mutex_unlock(&pci_epf_mutex);
		id++;
	}

	return 0;
}