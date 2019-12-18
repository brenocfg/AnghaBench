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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLPAR_KOBJ_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  dlpar_attr_group ; 
 int /*<<< orphan*/  dlpar_kobj ; 
 int /*<<< orphan*/  kobject_create_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 TYPE_1__* pci_slots_kset ; 
 int sysfs_create_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dlpar_sysfs_init(void)
{
	int error;

	dlpar_kobj = kobject_create_and_add(DLPAR_KOBJ_NAME,
					    &pci_slots_kset->kobj);
	if (!dlpar_kobj)
		return -EINVAL;

	error = sysfs_create_group(dlpar_kobj, &dlpar_attr_group);
	if (error)
		kobject_put(dlpar_kobj);
	return error;
}