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
struct dm_dirty_log_type {int /*<<< orphan*/  module; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  __find_dirty_log_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lock ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_type(struct dm_dirty_log_type *type)
{
	if (!type)
		return;

	spin_lock(&_lock);
	if (!__find_dirty_log_type(type->name))
		goto out;

	module_put(type->module);

out:
	spin_unlock(&_lock);
}