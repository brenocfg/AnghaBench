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
typedef  int /*<<< orphan*/  u64 ;
struct multicall_space {int /*<<< orphan*/ * args; int /*<<< orphan*/ * mc; } ;
struct mc_buffer {unsigned int argidx; size_t mcidx; int /*<<< orphan*/ * args; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int MC_ARGS ; 
 size_t MC_BATCH ; 
 int /*<<< orphan*/  XEN_MC_FL_ARGS ; 
 int /*<<< orphan*/  XEN_MC_FL_BATCH ; 
 int /*<<< orphan*/  mc_buffer ; 
 int preemptible () ; 
 unsigned int roundup (unsigned int,int) ; 
 struct mc_buffer* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xen_mc_entry_alloc (size_t) ; 
 int /*<<< orphan*/  trace_xen_mc_flush_reason (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xen_mc_flush () ; 

struct multicall_space __xen_mc_entry(size_t args)
{
	struct mc_buffer *b = this_cpu_ptr(&mc_buffer);
	struct multicall_space ret;
	unsigned argidx = roundup(b->argidx, sizeof(u64));

	trace_xen_mc_entry_alloc(args);

	BUG_ON(preemptible());
	BUG_ON(b->argidx >= MC_ARGS);

	if (unlikely(b->mcidx == MC_BATCH ||
		     (argidx + args) >= MC_ARGS)) {
		trace_xen_mc_flush_reason((b->mcidx == MC_BATCH) ?
					  XEN_MC_FL_BATCH : XEN_MC_FL_ARGS);
		xen_mc_flush();
		argidx = roundup(b->argidx, sizeof(u64));
	}

	ret.mc = &b->entries[b->mcidx];
#if MC_DEBUG
	b->caller[b->mcidx] = __builtin_return_address(0);
#endif
	b->mcidx++;
	ret.args = &b->args[argidx];
	b->argidx = argidx + args;

	BUG_ON(b->argidx >= MC_ARGS);
	return ret;
}