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
struct efivar_entry {int /*<<< orphan*/  scanning; } ;
typedef  char efi_char16_t ;

/* Variables and functions */
 int DUMP_NAME_LEN ; 
 int EINTR ; 
 int ENOENT ; 
 int __efivar_entry_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,struct efivar_entry**) ; 
 int /*<<< orphan*/  efi_pstore_erase_func ; 
 scalar_t__ efivar_entry_iter_begin () ; 
 int /*<<< orphan*/  efivar_entry_iter_end () ; 
 int /*<<< orphan*/  efivar_sysfs_list ; 
 int /*<<< orphan*/  efivar_unregister (struct efivar_entry*) ; 

__attribute__((used)) static int efi_pstore_erase_name(const char *name)
{
	struct efivar_entry *entry = NULL;
	efi_char16_t efi_name[DUMP_NAME_LEN];
	int found, i;

	for (i = 0; i < DUMP_NAME_LEN; i++) {
		efi_name[i] = name[i];
		if (name[i] == '\0')
			break;
	}

	if (efivar_entry_iter_begin())
		return -EINTR;

	found = __efivar_entry_iter(efi_pstore_erase_func, &efivar_sysfs_list,
				    efi_name, &entry);
	efivar_entry_iter_end();

	if (found && !entry->scanning)
		efivar_unregister(entry);

	return found ? 0 : -ENOENT;
}