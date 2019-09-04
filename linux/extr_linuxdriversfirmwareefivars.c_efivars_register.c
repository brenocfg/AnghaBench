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
struct efivars {struct kobject* kobject; struct efivar_operations const* ops; } ;
struct efivar_operations {int dummy; } ;

/* Variables and functions */
 int EINTR ; 
 struct efivars* __efivars ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efivars_lock ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int efivars_register(struct efivars *efivars,
		     const struct efivar_operations *ops,
		     struct kobject *kobject)
{
	if (down_interruptible(&efivars_lock))
		return -EINTR;

	efivars->ops = ops;
	efivars->kobject = kobject;

	__efivars = efivars;

	pr_info("Registered efivars operations\n");

	up(&efivars_lock);

	return 0;
}