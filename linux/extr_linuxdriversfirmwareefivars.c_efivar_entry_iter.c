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

/* Variables and functions */
 int __efivar_entry_iter (int (*) (struct efivar_entry*,void*),struct list_head*,void*,int /*<<< orphan*/ *) ; 
 int efivar_entry_iter_begin () ; 
 int /*<<< orphan*/  efivar_entry_iter_end () ; 

int efivar_entry_iter(int (*func)(struct efivar_entry *, void *),
		      struct list_head *head, void *data)
{
	int err = 0;

	err = efivar_entry_iter_begin();
	if (err)
		return err;
	err = __efivar_entry_iter(func, head, data, NULL);
	efivar_entry_iter_end();

	return err;
}