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
struct kvmppc_vcpu_e500 {int dummy; } ;
struct kvm_book3e_206_tlb_entry {scalar_t__ mas1; } ;

/* Variables and functions */
 struct kvm_book3e_206_tlb_entry* get_entry (struct kvmppc_vcpu_e500*,int,int) ; 
 int /*<<< orphan*/  get_tlb_iprot (struct kvm_book3e_206_tlb_entry*) ; 
 scalar_t__ kvmppc_need_recalc_tlb1map_range (struct kvmppc_vcpu_e500*,struct kvm_book3e_206_tlb_entry*) ; 
 int /*<<< orphan*/  kvmppc_recalc_tlb1map_range (struct kvmppc_vcpu_e500*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int kvmppc_e500_gtlbe_invalidate(
				struct kvmppc_vcpu_e500 *vcpu_e500,
				int tlbsel, int esel)
{
	struct kvm_book3e_206_tlb_entry *gtlbe =
		get_entry(vcpu_e500, tlbsel, esel);

	if (unlikely(get_tlb_iprot(gtlbe)))
		return -1;

	if (tlbsel == 1 && kvmppc_need_recalc_tlb1map_range(vcpu_e500, gtlbe))
		kvmppc_recalc_tlb1map_range(vcpu_e500);

	gtlbe->mas1 = 0;

	return 0;
}