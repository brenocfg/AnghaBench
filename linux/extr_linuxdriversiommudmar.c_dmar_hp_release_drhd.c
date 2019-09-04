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
struct dmar_drhd_unit {int /*<<< orphan*/  list; } ;
struct acpi_dmar_header {int dummy; } ;
struct acpi_dmar_hardware_unit {int dummy; } ;

/* Variables and functions */
 struct dmar_drhd_unit* dmar_find_dmaru (struct acpi_dmar_hardware_unit*) ; 
 int /*<<< orphan*/  dmar_free_drhd (struct dmar_drhd_unit*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int dmar_hp_release_drhd(struct acpi_dmar_header *header, void *arg)
{
	struct dmar_drhd_unit *dmaru;

	dmaru = dmar_find_dmaru((struct acpi_dmar_hardware_unit *)header);
	if (dmaru) {
		list_del_rcu(&dmaru->list);
		synchronize_rcu();
		dmar_free_drhd(dmaru);
	}

	return 0;
}