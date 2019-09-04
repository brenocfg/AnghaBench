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
struct efivar_entry {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efivars_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int efivar_entry_add(struct efivar_entry *entry, struct list_head *head)
{
	if (down_interruptible(&efivars_lock))
		return -EINTR;
	list_add(&entry->list, head);
	up(&efivars_lock);

	return 0;
}