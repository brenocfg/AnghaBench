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
struct dm_dirty_log_type {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 struct dm_dirty_log_type* __find_dirty_log_type (char const*) ; 
 int /*<<< orphan*/  _lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dm_dirty_log_type *_get_dirty_log_type(const char *name)
{
	struct dm_dirty_log_type *log_type;

	spin_lock(&_lock);

	log_type = __find_dirty_log_type(name);
	if (log_type && !try_module_get(log_type->module))
		log_type = NULL;

	spin_unlock(&_lock);

	return log_type;
}