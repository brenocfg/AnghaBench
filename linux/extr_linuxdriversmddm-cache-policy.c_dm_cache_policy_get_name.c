#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dm_cache_policy_type {char const* name; TYPE_1__* real; } ;
struct dm_cache_policy {struct dm_cache_policy_type* private; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */

const char *dm_cache_policy_get_name(struct dm_cache_policy *p)
{
	struct dm_cache_policy_type *t = p->private;

	/* if t->real is set then an alias was used (e.g. "default") */
	if (t->real)
		return t->real->name;

	return t->name;
}