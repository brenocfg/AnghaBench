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
struct TYPE_2__ {int /*<<< orphan*/  VariableName; int /*<<< orphan*/  VendorGuid; } ;
struct efivar_entry {int deleting; int /*<<< orphan*/  list; scalar_t__ scanning; TYPE_1__ var; } ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_EFI_CRASH_GUID ; 
 int /*<<< orphan*/  __efivar_entry_delete (struct efivar_entry*) ; 
 scalar_t__ efi_guidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 unsigned long ucs2_strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ ucs2_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int efi_pstore_erase_func(struct efivar_entry *entry, void *data)
{
	efi_char16_t *efi_name = data;
	efi_guid_t vendor = LINUX_EFI_CRASH_GUID;
	unsigned long ucs2_len = ucs2_strlen(efi_name);

	if (efi_guidcmp(entry->var.VendorGuid, vendor))
		return 0;

	if (ucs2_strncmp(entry->var.VariableName, efi_name, (size_t)ucs2_len))
		return 0;

	if (entry->scanning) {
		/*
		 * Skip deletion because this entry will be deleted
		 * after scanning is completed.
		 */
		entry->deleting = true;
	} else
		list_del(&entry->list);

	/* found */
	__efivar_entry_delete(entry);

	return 1;
}