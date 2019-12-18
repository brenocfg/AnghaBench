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
struct dm_exception_store_type {int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  __find_exception_store_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exception_store_types ; 
 int /*<<< orphan*/  _lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dm_exception_store_type_register(struct dm_exception_store_type *type)
{
	int r = 0;

	spin_lock(&_lock);
	if (!__find_exception_store_type(type->name))
		list_add(&type->list, &_exception_store_types);
	else
		r = -EEXIST;
	spin_unlock(&_lock);

	return r;
}