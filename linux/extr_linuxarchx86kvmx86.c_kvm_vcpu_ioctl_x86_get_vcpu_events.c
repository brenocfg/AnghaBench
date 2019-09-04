#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int smm_inside_nmi; int /*<<< orphan*/  latched_init; int /*<<< orphan*/  pending; int /*<<< orphan*/  smm; } ;
struct TYPE_13__ {int pending; scalar_t__ pad; int /*<<< orphan*/  masked; int /*<<< orphan*/  injected; } ;
struct TYPE_12__ {int injected; int /*<<< orphan*/  shadow; scalar_t__ soft; int /*<<< orphan*/  nr; } ;
struct TYPE_9__ {int injected; int /*<<< orphan*/  error_code; scalar_t__ pad; int /*<<< orphan*/  has_error_code; int /*<<< orphan*/  nr; } ;
struct kvm_vcpu_events {int flags; int /*<<< orphan*/  reserved; TYPE_7__ smi; scalar_t__ sipi_vector; TYPE_5__ nmi; TYPE_4__ interrupt; TYPE_1__ exception; } ;
struct TYPE_11__ {int /*<<< orphan*/  nr; int /*<<< orphan*/  soft; scalar_t__ injected; } ;
struct TYPE_10__ {int /*<<< orphan*/  error_code; int /*<<< orphan*/  has_error_code; int /*<<< orphan*/  nr; scalar_t__ injected; scalar_t__ pending; } ;
struct TYPE_14__ {scalar_t__ nmi_pending; int hflags; int /*<<< orphan*/  smi_pending; int /*<<< orphan*/  nmi_injected; TYPE_3__ interrupt; TYPE_2__ exception; } ;
struct kvm_vcpu {TYPE_6__ arch; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* get_nmi_mask ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* get_interrupt_shadow ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int HF_SMM_INSIDE_NMI_MASK ; 
 int KVM_VCPUEVENT_VALID_NMI_PENDING ; 
 int KVM_VCPUEVENT_VALID_SHADOW ; 
 int KVM_VCPUEVENT_VALID_SMM ; 
 int /*<<< orphan*/  is_smm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_exception_is_soft (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_lapic_latched_init (struct kvm_vcpu*) ; 
 TYPE_8__* kvm_x86_ops ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_nmi (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_vcpu_ioctl_x86_get_vcpu_events(struct kvm_vcpu *vcpu,
					       struct kvm_vcpu_events *events)
{
	process_nmi(vcpu);
	/*
	 * FIXME: pass injected and pending separately.  This is only
	 * needed for nested virtualization, whose state cannot be
	 * migrated yet.  For now we can combine them.
	 */
	events->exception.injected =
		(vcpu->arch.exception.pending ||
		 vcpu->arch.exception.injected) &&
		!kvm_exception_is_soft(vcpu->arch.exception.nr);
	events->exception.nr = vcpu->arch.exception.nr;
	events->exception.has_error_code = vcpu->arch.exception.has_error_code;
	events->exception.pad = 0;
	events->exception.error_code = vcpu->arch.exception.error_code;

	events->interrupt.injected =
		vcpu->arch.interrupt.injected && !vcpu->arch.interrupt.soft;
	events->interrupt.nr = vcpu->arch.interrupt.nr;
	events->interrupt.soft = 0;
	events->interrupt.shadow = kvm_x86_ops->get_interrupt_shadow(vcpu);

	events->nmi.injected = vcpu->arch.nmi_injected;
	events->nmi.pending = vcpu->arch.nmi_pending != 0;
	events->nmi.masked = kvm_x86_ops->get_nmi_mask(vcpu);
	events->nmi.pad = 0;

	events->sipi_vector = 0; /* never valid when reporting to user space */

	events->smi.smm = is_smm(vcpu);
	events->smi.pending = vcpu->arch.smi_pending;
	events->smi.smm_inside_nmi =
		!!(vcpu->arch.hflags & HF_SMM_INSIDE_NMI_MASK);
	events->smi.latched_init = kvm_lapic_latched_init(vcpu);

	events->flags = (KVM_VCPUEVENT_VALID_NMI_PENDING
			 | KVM_VCPUEVENT_VALID_SHADOW
			 | KVM_VCPUEVENT_VALID_SMM);
	memset(&events->reserved, 0, sizeof(events->reserved));
}