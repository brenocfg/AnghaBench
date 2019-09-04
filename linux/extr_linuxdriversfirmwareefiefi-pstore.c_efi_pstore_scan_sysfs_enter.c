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
struct list_head {int dummy; } ;
struct efivar_entry {int scanning; struct list_head list; } ;

/* Variables and functions */

__attribute__((used)) static void efi_pstore_scan_sysfs_enter(struct efivar_entry *pos,
					struct efivar_entry *next,
					struct list_head *head)
{
	pos->scanning = true;
	if (&next->list != head)
		next->scanning = true;
}