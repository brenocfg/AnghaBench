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
struct static_dep_map {scalar_t__ to; scalar_t__ from; } ;
struct clockdomain {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int clkdm_add_wkdep (struct clockdomain*,struct clockdomain*) ; 
 struct clockdomain* clkdm_lookup (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static inline int omap4plus_init_static_deps(const struct static_dep_map *map)
{
	int ret;
	struct clockdomain *from, *to;

	if (!map)
		return 0;

	while (map->from) {
		from = clkdm_lookup(map->from);
		to = clkdm_lookup(map->to);
		if (!from || !to) {
			pr_err("Failed lookup %s or %s for wakeup dependency\n",
			       map->from, map->to);
			return -EINVAL;
		}
		ret = clkdm_add_wkdep(from, to);
		if (ret) {
			pr_err("Failed to add %s -> %s wakeup dependency(%d)\n",
			       map->from, map->to, ret);
			return ret;
		}

		map++;
	}

	return 0;
}