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
struct efivar_entry {int dummy; } ;

/* Variables and functions */
 int efivar_entry_remove (struct efivar_entry*) ; 
 int /*<<< orphan*/  efivar_unregister (struct efivar_entry*) ; 

__attribute__((used)) static int efivar_sysfs_destroy(struct efivar_entry *entry, void *data)
{
	int err = efivar_entry_remove(entry);

	if (err)
		return err;
	efivar_unregister(entry);
	return 0;
}