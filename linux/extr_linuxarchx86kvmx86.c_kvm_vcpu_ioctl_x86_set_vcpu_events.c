#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_15__ {scalar_t__ latched_init; scalar_t__ smm_inside_nmi; scalar_t__ smm; scalar_t__ pending; } ;
struct TYPE_14__ {int /*<<< orphan*/  masked; int /*<<< orphan*/  pending; int /*<<< orphan*/  injected; } ;
struct TYPE_13__ {int /*<<< orphan*/  shadow; int /*<<< orphan*/  soft; int /*<<< orphan*/  nr; int /*<<< orphan*/  injected; } ;
struct TYPE_11__ {int nr; int /*<<< orphan*/  error_code; int /*<<< orphan*/  has_error_code; scalar_t__ injected; } ;
struct kvm_vcpu_events {int flags; TYPE_6__ smi; int /*<<< orphan*/  sipi_vector; TYPE_5__ nmi; TYPE_4__ interrupt; TYPE_2__ exception; } ;
struct TYPE_12__ {int /*<<< orphan*/  soft; int /*<<< orphan*/  nr; int /*<<< orphan*/  injected; } ;
struct TYPE_10__ {int injected; int nr; int /*<<< orphan*/  error_code; int /*<<< orphan*/  has_error_code; scalar_t__ pending; } ;
struct TYPE_17__ {scalar_t__ mp_state; TYPE_7__* apic; int /*<<< orphan*/  hflags; scalar_t__ smi_pending; int /*<<< orphan*/  nmi_pending; int /*<<< orphan*/  nmi_injected; TYPE_3__ interrupt; TYPE_1__ exception; } ;
struct kvm_vcpu {TYPE_8__ arch; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* set_nmi_mask ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_interrupt_shadow ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  pending_events; int /*<<< orphan*/  sipi_vector; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HF_SMM_INSIDE_NMI_MASK ; 
 int /*<<< orphan*/  HF_SMM_MASK ; 
 int /*<<< orphan*/  KVM_APIC_INIT ; 
 scalar_t__ KVM_MP_STATE_INIT_RECEIVED ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int KVM_VCPUEVENT_VALID_NMI_PENDING ; 
 int KVM_VCPUEVENT_VALID_SHADOW ; 
 int KVM_VCPUEVENT_VALID_SIPI_VECTOR ; 
 int KVM_VCPUEVENT_VALID_SMM ; 
 int NMI_VECTOR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_set_hflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_9__* kvm_x86_ops ; 
 scalar_t__ lapic_in_kernel (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  process_nmi (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_vcpu_ioctl_x86_set_vcpu_events(struct kvm_vcpu *vcpu,
					      struct kvm_vcpu_events *events)
{
	if (events->flags & ~(KVM_VCPUEVENT_VALID_NMI_PENDING
			      | KVM_VCPUEVENT_VALID_SIPI_VECTOR
			      | KVM_VCPUEVENT_VALID_SHADOW
			      | KVM_VCPUEVENT_VALID_SMM))
		return -EINVAL;

	if (events->exception.injected &&
	    (events->exception.nr > 31 || events->exception.nr == NMI_VECTOR ||
	     is_guest_mode(vcpu)))
		return -EINVAL;

	/* INITs are latched while in SMM */
	if (events->flags & KVM_VCPUEVENT_VALID_SMM &&
	    (events->smi.smm || events->smi.pending) &&
	    vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED)
		return -EINVAL;

	process_nmi(vcpu);
	vcpu->arch.exception.injected = false;
	vcpu->arch.exception.pending = events->exception.injected;
	vcpu->arch.exception.nr = events->exception.nr;
	vcpu->arch.exception.has_error_code = events->exception.has_error_code;
	vcpu->arch.exception.error_code = events->exception.error_code;

	vcpu->arch.interrupt.injected = events->interrupt.injected;
	vcpu->arch.interrupt.nr = events->interrupt.nr;
	vcpu->arch.interrupt.soft = events->interrupt.soft;
	if (events->flags & KVM_VCPUEVENT_VALID_SHADOW)
		kvm_x86_ops->set_interrupt_shadow(vcpu,
						  events->interrupt.shadow);

	vcpu->arch.nmi_injected = events->nmi.injected;
	if (events->flags & KVM_VCPUEVENT_VALID_NMI_PENDING)
		vcpu->arch.nmi_pending = events->nmi.pending;
	kvm_x86_ops->set_nmi_mask(vcpu, events->nmi.masked);

	if (events->flags & KVM_VCPUEVENT_VALID_SIPI_VECTOR &&
	    lapic_in_kernel(vcpu))
		vcpu->arch.apic->sipi_vector = events->sipi_vector;

	if (events->flags & KVM_VCPUEVENT_VALID_SMM) {
		u32 hflags = vcpu->arch.hflags;
		if (events->smi.smm)
			hflags |= HF_SMM_MASK;
		else
			hflags &= ~HF_SMM_MASK;
		kvm_set_hflags(vcpu, hflags);

		vcpu->arch.smi_pending = events->smi.pending;

		if (events->smi.smm) {
			if (events->smi.smm_inside_nmi)
				vcpu->arch.hflags |= HF_SMM_INSIDE_NMI_MASK;
			else
				vcpu->arch.hflags &= ~HF_SMM_INSIDE_NMI_MASK;
			if (lapic_in_kernel(vcpu)) {
				if (events->smi.latched_init)
					set_bit(KVM_APIC_INIT, &vcpu->arch.apic->pending_events);
				else
					clear_bit(KVM_APIC_INIT, &vcpu->arch.apic->pending_events);
			}
		}
	}

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	return 0;
}