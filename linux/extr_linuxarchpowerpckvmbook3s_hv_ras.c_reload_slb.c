#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct slb_shadow {TYPE_1__* save_area; int /*<<< orphan*/  persistent; } ;
struct TYPE_6__ {void* pinned_end; struct slb_shadow* pinned_addr; } ;
struct TYPE_5__ {TYPE_3__ slb_shadow; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  vsid; int /*<<< orphan*/  esid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLB_MIN_SIZE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void reload_slb(struct kvm_vcpu *vcpu)
{
	struct slb_shadow *slb;
	unsigned long i, n;

	/* First clear out SLB */
	asm volatile("slbmte %0,%0; slbia" : : "r" (0));

	/* Do they have an SLB shadow buffer registered? */
	slb = vcpu->arch.slb_shadow.pinned_addr;
	if (!slb)
		return;

	/* Sanity check */
	n = min_t(u32, be32_to_cpu(slb->persistent), SLB_MIN_SIZE);
	if ((void *) &slb->save_area[n] > vcpu->arch.slb_shadow.pinned_end)
		return;

	/* Load up the SLB from that */
	for (i = 0; i < n; ++i) {
		unsigned long rb = be64_to_cpu(slb->save_area[i].esid);
		unsigned long rs = be64_to_cpu(slb->save_area[i].vsid);

		rb = (rb & ~0xFFFul) | i;	/* insert entry number */
		asm volatile("slbmte %0,%1" : : "r" (rs), "r" (rb));
	}
}