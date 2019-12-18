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
struct dm_cache_policy_type {unsigned int const* version; } ;
struct dm_cache_policy {struct dm_cache_policy_type* private; } ;

/* Variables and functions */

const unsigned *dm_cache_policy_get_version(struct dm_cache_policy *p)
{
	struct dm_cache_policy_type *t = p->private;

	return t->version;
}