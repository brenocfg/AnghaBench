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
struct kobject {int dummy; } ;
struct efi_runtime_map_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct efi_runtime_map_entry*) ; 
 struct efi_runtime_map_entry* to_map_entry (struct kobject*) ; 

__attribute__((used)) static void map_release(struct kobject *kobj)
{
	struct efi_runtime_map_entry *entry;

	entry = to_map_entry(kobj);
	kfree(entry);
}