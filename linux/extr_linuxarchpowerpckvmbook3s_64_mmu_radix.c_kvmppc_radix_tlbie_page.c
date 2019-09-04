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
struct TYPE_2__ {int /*<<< orphan*/  lpid; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  radix__flush_tlb_lpid_page (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static void kvmppc_radix_tlbie_page(struct kvm *kvm, unsigned long addr,
				    unsigned int pshift)
{
	unsigned long psize = PAGE_SIZE;

	if (pshift)
		psize = 1UL << pshift;

	addr &= ~(psize - 1);
	radix__flush_tlb_lpid_page(kvm->arch.lpid, addr, psize);
}