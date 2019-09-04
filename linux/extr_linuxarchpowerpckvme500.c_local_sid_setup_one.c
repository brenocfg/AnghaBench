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
struct id {unsigned long val; int /*<<< orphan*/  pentry; } ;
struct TYPE_2__ {int /*<<< orphan*/ * entry; } ;

/* Variables and functions */
 unsigned long NUM_TIDS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long __this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,struct id*) ; 
 int /*<<< orphan*/  pcpu_last_used_sid ; 
 TYPE_1__ pcpu_sids ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int local_sid_setup_one(struct id *entry)
{
	unsigned long sid;
	int ret = -1;

	sid = __this_cpu_inc_return(pcpu_last_used_sid);
	if (sid < NUM_TIDS) {
		__this_cpu_write(pcpu_sids.entry[sid], entry);
		entry->val = sid;
		entry->pentry = this_cpu_ptr(&pcpu_sids.entry[sid]);
		ret = sid;
	}

	/*
	 * If sid == NUM_TIDS, we've run out of sids.  We return -1, and
	 * the caller will invalidate everything and start over.
	 *
	 * sid > NUM_TIDS indicates a race, which we disable preemption to
	 * avoid.
	 */
	WARN_ON(sid > NUM_TIDS);

	return ret;
}