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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 unsigned int get_mmio_spte_generation (int /*<<< orphan*/ ) ; 
 unsigned int kvm_current_mmio_generation (struct kvm_vcpu*) ; 
 int likely (int) ; 
 int /*<<< orphan*/  trace_check_mmio_spte (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static bool check_mmio_spte(struct kvm_vcpu *vcpu, u64 spte)
{
	unsigned int kvm_gen, spte_gen;

	kvm_gen = kvm_current_mmio_generation(vcpu);
	spte_gen = get_mmio_spte_generation(spte);

	trace_check_mmio_spte(spte, kvm_gen, spte_gen);
	return likely(kvm_gen == spte_gen);
}