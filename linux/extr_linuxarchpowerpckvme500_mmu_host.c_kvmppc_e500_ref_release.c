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
struct tlbe_ref {int flags; int /*<<< orphan*/  pfn; } ;

/* Variables and functions */
 int E500_TLB_VALID ; 
 int /*<<< orphan*/  trace_kvm_booke206_ref_release (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void kvmppc_e500_ref_release(struct tlbe_ref *ref)
{
	if (ref->flags & E500_TLB_VALID) {
		/* FIXME: don't log bogus pfn for TLB1 */
		trace_kvm_booke206_ref_release(ref->pfn, ref->flags);
		ref->flags = 0;
	}
}