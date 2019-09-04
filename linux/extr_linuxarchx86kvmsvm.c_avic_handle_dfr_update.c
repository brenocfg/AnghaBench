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
typedef  int u32 ;
struct vcpu_svm {scalar_t__ ldr_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;
struct kvm_svm {int ldr_mode; int /*<<< orphan*/  avic_logical_id_table_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DFR ; 
 int /*<<< orphan*/  avic_handle_ldr_update (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  clear_page (int /*<<< orphan*/ ) ; 
 int kvm_lapic_get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 struct kvm_svm* to_kvm_svm (int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static int avic_handle_dfr_update(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	struct kvm_svm *kvm_svm = to_kvm_svm(vcpu->kvm);
	u32 dfr = kvm_lapic_get_reg(vcpu->arch.apic, APIC_DFR);
	u32 mod = (dfr >> 28) & 0xf;

	/*
	 * We assume that all local APICs are using the same type.
	 * If this changes, we need to flush the AVIC logical
	 * APID id table.
	 */
	if (kvm_svm->ldr_mode == mod)
		return 0;

	clear_page(page_address(kvm_svm->avic_logical_id_table_page));
	kvm_svm->ldr_mode = mod;

	if (svm->ldr_reg)
		avic_handle_ldr_update(vcpu);
	return 0;
}