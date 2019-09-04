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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_tlb1_bitmap (struct kvmppc_vcpu_e500*) ; 
 int /*<<< orphan*/  clear_tlb_privs (struct kvmppc_vcpu_e500*) ; 
 int /*<<< orphan*/  kvmppc_e500_tlbil_all (struct kvmppc_vcpu_e500*) ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

void kvmppc_core_flush_tlb(struct kvm_vcpu *vcpu)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	kvmppc_e500_tlbil_all(vcpu_e500);
	clear_tlb_privs(vcpu_e500);
	clear_tlb1_bitmap(vcpu_e500);
}