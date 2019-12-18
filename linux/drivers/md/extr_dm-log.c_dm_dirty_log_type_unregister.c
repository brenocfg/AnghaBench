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
struct dm_dirty_log_type {int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __find_dirty_log_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dm_dirty_log_type_unregister(struct dm_dirty_log_type *type)
{
	spin_lock(&_lock);

	if (!__find_dirty_log_type(type->name)) {
		spin_unlock(&_lock);
		return -EINVAL;
	}

	list_del(&type->list);

	spin_unlock(&_lock);

	return 0;
}