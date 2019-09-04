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
struct work_struct {int dummy; } ;
struct efivar_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  efivar_create_sysfs_entry (struct efivar_entry*) ; 
 int efivar_init (int /*<<< orphan*/ ,struct efivar_entry*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efivar_sysfs_list ; 
 int /*<<< orphan*/  efivar_update_sysfs_entry ; 
 int /*<<< orphan*/  kfree (struct efivar_entry*) ; 
 struct efivar_entry* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void efivar_update_sysfs_entries(struct work_struct *work)
{
	struct efivar_entry *entry;
	int err;

	/* Add new sysfs entries */
	while (1) {
		entry = kzalloc(sizeof(*entry), GFP_KERNEL);
		if (!entry)
			return;

		err = efivar_init(efivar_update_sysfs_entry, entry,
				  false, &efivar_sysfs_list);
		if (!err)
			break;

		efivar_create_sysfs_entry(entry);
	}

	kfree(entry);
}