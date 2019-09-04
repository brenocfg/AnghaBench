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
struct TYPE_2__ {int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/ * VariableName; } ;
struct efivar_entry {TYPE_1__ var; } ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */
 scalar_t__ efivar_entry_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  efivar_sysfs_list ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int efivar_update_sysfs_entry(efi_char16_t *name, efi_guid_t vendor,
				     unsigned long name_size, void *data)
{
	struct efivar_entry *entry = data;

	if (efivar_entry_find(name, vendor, &efivar_sysfs_list, false))
		return 0;

	memcpy(entry->var.VariableName, name, name_size);
	memcpy(&(entry->var.VendorGuid), &vendor, sizeof(efi_guid_t));

	return 1;
}