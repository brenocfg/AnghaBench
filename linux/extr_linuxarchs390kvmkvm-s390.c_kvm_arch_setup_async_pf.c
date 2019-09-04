#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ pfault_token; int pfault_select; int pfault_compare; TYPE_3__* gmap; TYPE_2__* sie_block; } ;
struct kvm_vcpu {TYPE_4__ arch; int /*<<< orphan*/  kvm; } ;
struct kvm_arch_async_pf {int /*<<< orphan*/  pfault_token; } ;
typedef  int hva_t ;
struct TYPE_11__ {int gmap_addr; } ;
struct TYPE_12__ {TYPE_5__ thread; } ;
struct TYPE_9__ {int /*<<< orphan*/  pfault_enabled; } ;
struct TYPE_7__ {int mask; } ;
struct TYPE_8__ {int* gcr; TYPE_1__ gpsw; } ;

/* Variables and functions */
 int CR0_SERVICE_SIGNAL_SUBMASK ; 
 scalar_t__ KVM_S390_PFAULT_TOKEN_INVALID ; 
 int PAGE_MASK ; 
 TYPE_6__* current ; 
 int gfn_to_hva (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpa_to_gfn (int) ; 
 scalar_t__ kvm_s390_vcpu_has_irq (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_setup_async_pf (struct kvm_vcpu*,int,int,struct kvm_arch_async_pf*) ; 
 scalar_t__ psw_extint_disabled (struct kvm_vcpu*) ; 
 scalar_t__ read_guest_real (struct kvm_vcpu*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int kvm_arch_setup_async_pf(struct kvm_vcpu *vcpu)
{
	hva_t hva;
	struct kvm_arch_async_pf arch;
	int rc;

	if (vcpu->arch.pfault_token == KVM_S390_PFAULT_TOKEN_INVALID)
		return 0;
	if ((vcpu->arch.sie_block->gpsw.mask & vcpu->arch.pfault_select) !=
	    vcpu->arch.pfault_compare)
		return 0;
	if (psw_extint_disabled(vcpu))
		return 0;
	if (kvm_s390_vcpu_has_irq(vcpu, 0))
		return 0;
	if (!(vcpu->arch.sie_block->gcr[0] & CR0_SERVICE_SIGNAL_SUBMASK))
		return 0;
	if (!vcpu->arch.gmap->pfault_enabled)
		return 0;

	hva = gfn_to_hva(vcpu->kvm, gpa_to_gfn(current->thread.gmap_addr));
	hva += current->thread.gmap_addr & ~PAGE_MASK;
	if (read_guest_real(vcpu, vcpu->arch.pfault_token, &arch.pfault_token, 8))
		return 0;

	rc = kvm_setup_async_pf(vcpu, current->thread.gmap_addr, hva, &arch);
	return rc;
}