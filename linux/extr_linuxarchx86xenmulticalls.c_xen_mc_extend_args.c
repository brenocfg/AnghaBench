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
struct multicall_space {int /*<<< orphan*/ * args; TYPE_1__* mc; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct mc_buffer {size_t argidx; int mcidx; int /*<<< orphan*/ * args; TYPE_1__* entries; } ;
struct TYPE_2__ {unsigned long op; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t MC_ARGS ; 
 int /*<<< orphan*/  XEN_MC_XE_BAD_OP ; 
 int /*<<< orphan*/  XEN_MC_XE_NO_SPACE ; 
 int /*<<< orphan*/  XEN_MC_XE_OK ; 
 int /*<<< orphan*/  mc_buffer ; 
 int preemptible () ; 
 struct mc_buffer* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xen_mc_extend_args (unsigned long,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct multicall_space xen_mc_extend_args(unsigned long op, size_t size)
{
	struct mc_buffer *b = this_cpu_ptr(&mc_buffer);
	struct multicall_space ret = { NULL, NULL };

	BUG_ON(preemptible());
	BUG_ON(b->argidx >= MC_ARGS);

	if (unlikely(b->mcidx == 0 ||
		     b->entries[b->mcidx - 1].op != op)) {
		trace_xen_mc_extend_args(op, size, XEN_MC_XE_BAD_OP);
		goto out;
	}

	if (unlikely((b->argidx + size) >= MC_ARGS)) {
		trace_xen_mc_extend_args(op, size, XEN_MC_XE_NO_SPACE);
		goto out;
	}

	ret.mc = &b->entries[b->mcidx - 1];
	ret.args = &b->args[b->argidx];
	b->argidx += size;

	BUG_ON(b->argidx >= MC_ARGS);

	trace_xen_mc_extend_args(op, size, XEN_MC_XE_OK);
out:
	return ret;
}