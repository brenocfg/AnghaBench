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
struct dm_cache_policy_type {int dummy; } ;

/* Variables and functions */
 struct dm_cache_policy_type* __get_policy_once (char const*) ; 
 int /*<<< orphan*/  register_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dm_cache_policy_type *get_policy_once(const char *name)
{
	struct dm_cache_policy_type *t;

	spin_lock(&register_lock);
	t = __get_policy_once(name);
	spin_unlock(&register_lock);

	return t;
}