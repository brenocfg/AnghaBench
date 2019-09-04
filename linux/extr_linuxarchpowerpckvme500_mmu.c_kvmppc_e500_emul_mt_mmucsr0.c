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
typedef  int ulong ;
struct kvmppc_vcpu_e500 {int /*<<< orphan*/  vcpu; TYPE_1__* gtlb_params; } ;
struct TYPE_2__ {int entries; } ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int MMUCSR0_TLB0FI ; 
 int MMUCSR0_TLB1FI ; 
 int /*<<< orphan*/  kvmppc_core_flush_tlb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_e500_gtlbe_invalidate (struct kvmppc_vcpu_e500*,int,int) ; 

int kvmppc_e500_emul_mt_mmucsr0(struct kvmppc_vcpu_e500 *vcpu_e500, ulong value)
{
	int esel;

	if (value & MMUCSR0_TLB0FI)
		for (esel = 0; esel < vcpu_e500->gtlb_params[0].entries; esel++)
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, 0, esel);
	if (value & MMUCSR0_TLB1FI)
		for (esel = 0; esel < vcpu_e500->gtlb_params[1].entries; esel++)
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, 1, esel);

	/* Invalidate all host shadow mappings */
	kvmppc_core_flush_tlb(&vcpu_e500->vcpu);

	return EMULATE_DONE;
}