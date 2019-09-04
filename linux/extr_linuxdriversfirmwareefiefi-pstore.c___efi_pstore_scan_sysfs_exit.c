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
struct efivar_entry {int scanning; int /*<<< orphan*/  list; scalar_t__ deleting; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ efivar_entry_iter_begin () ; 
 int /*<<< orphan*/  efivar_entry_iter_end () ; 
 int /*<<< orphan*/  efivar_unregister (struct efivar_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int __efi_pstore_scan_sysfs_exit(struct efivar_entry *entry,
						bool turn_off_scanning)
{
	if (entry->deleting) {
		list_del(&entry->list);
		efivar_entry_iter_end();
		efivar_unregister(entry);
		if (efivar_entry_iter_begin())
			return -EINTR;
	} else if (turn_off_scanning)
		entry->scanning = false;

	return 0;
}