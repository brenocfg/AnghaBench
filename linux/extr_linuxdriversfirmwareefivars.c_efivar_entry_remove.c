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
struct efivar_entry {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efivars_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int efivar_entry_remove(struct efivar_entry *entry)
{
	if (down_interruptible(&efivars_lock))
		return -EINTR;
	list_del(&entry->list);
	up(&efivars_lock);

	return 0;
}