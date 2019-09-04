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
union cache_topology {TYPE_1__* ci; int /*<<< orphan*/  raw; } ;
struct cpu_cacheinfo {unsigned int num_levels; unsigned int num_leaves; struct cacheinfo* info_list; } ;
struct cacheinfo {int dummy; } ;
typedef  enum cache_type { ____Placeholder_cache_type } cache_type ;
struct TYPE_2__ {scalar_t__ scope; } ;

/* Variables and functions */
 scalar_t__ CACHE_SCOPE_PRIVATE ; 
 int CACHE_TYPE_DATA ; 
 int CACHE_TYPE_INST ; 
 int CACHE_TYPE_SEPARATE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EXTRACT_TOPOLOGY ; 
 int /*<<< orphan*/  ci_leaf_init (int /*<<< orphan*/ ,unsigned int,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ecag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_cache_type (TYPE_1__*,unsigned int) ; 
 struct cpu_cacheinfo* get_cpu_cacheinfo (unsigned int) ; 
 int /*<<< orphan*/  test_facility (int) ; 

int populate_cache_leaves(unsigned int cpu)
{
	struct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	struct cacheinfo *this_leaf = this_cpu_ci->info_list;
	unsigned int level, idx, pvt;
	union cache_topology ct;
	enum cache_type ctype;

	if (!test_facility(34))
		return -EOPNOTSUPP;
	ct.raw = ecag(EXTRACT_TOPOLOGY, 0, 0);
	for (idx = 0, level = 0; level < this_cpu_ci->num_levels &&
	     idx < this_cpu_ci->num_leaves; idx++, level++) {
		if (!this_leaf)
			return -EINVAL;
		pvt = (ct.ci[level].scope == CACHE_SCOPE_PRIVATE) ? 1 : 0;
		ctype = get_cache_type(&ct.ci[0], level);
		if (ctype == CACHE_TYPE_SEPARATE) {
			ci_leaf_init(this_leaf++, pvt, CACHE_TYPE_DATA, level, cpu);
			ci_leaf_init(this_leaf++, pvt, CACHE_TYPE_INST, level, cpu);
		} else {
			ci_leaf_init(this_leaf++, pvt, ctype, level, cpu);
		}
	}
	return 0;
}