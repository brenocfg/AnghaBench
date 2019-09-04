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
struct dmar_dev_scope {int dummy; } ;
struct acpi_dmar_device_scope {scalar_t__ entry_type; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ ACPI_DMAR_SCOPE_TYPE_BRIDGE ; 
 scalar_t__ ACPI_DMAR_SCOPE_TYPE_ENDPOINT ; 
 scalar_t__ ACPI_DMAR_SCOPE_TYPE_HPET ; 
 scalar_t__ ACPI_DMAR_SCOPE_TYPE_IOAPIC ; 
 scalar_t__ ACPI_DMAR_SCOPE_TYPE_NAMESPACE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void *dmar_alloc_dev_scope(void *start, void *end, int *cnt)
{
	struct acpi_dmar_device_scope *scope;

	*cnt = 0;
	while (start < end) {
		scope = start;
		if (scope->entry_type == ACPI_DMAR_SCOPE_TYPE_NAMESPACE ||
		    scope->entry_type == ACPI_DMAR_SCOPE_TYPE_ENDPOINT ||
		    scope->entry_type == ACPI_DMAR_SCOPE_TYPE_BRIDGE)
			(*cnt)++;
		else if (scope->entry_type != ACPI_DMAR_SCOPE_TYPE_IOAPIC &&
			scope->entry_type != ACPI_DMAR_SCOPE_TYPE_HPET) {
			pr_warn("Unsupported device scope\n");
		}
		start += scope->length;
	}
	if (*cnt == 0)
		return NULL;

	return kcalloc(*cnt, sizeof(struct dmar_dev_scope), GFP_KERNEL);
}