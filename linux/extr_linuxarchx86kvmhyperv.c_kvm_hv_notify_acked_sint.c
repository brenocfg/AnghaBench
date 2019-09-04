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
typedef  size_t u32 ;
struct kvm_vcpu_hv_synic {int msg_page; int /*<<< orphan*/ * sint_to_gsi; } ;
struct kvm_vcpu_hv_stimer {int config; int /*<<< orphan*/  index; scalar_t__ msg_pending; } ;
struct kvm_vcpu_hv {int /*<<< orphan*/  stimer_pending_bitmap; struct kvm_vcpu_hv_stimer* stimer; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; struct kvm* kvm; } ;
struct kvm {int /*<<< orphan*/  irq_srcu; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct kvm_vcpu_hv_stimer*) ; 
 int HV_STIMER_ENABLE ; 
 size_t HV_STIMER_SINT (int) ; 
 int HV_SYNIC_SIMP_ENABLE ; 
 int /*<<< orphan*/  KVM_REQ_HV_STIMER ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_notify_acked_gsi (struct kvm*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  synic_clear_sint_msg_pending (struct kvm_vcpu_hv_synic*,size_t) ; 
 int /*<<< orphan*/  trace_kvm_hv_notify_acked_sint (int /*<<< orphan*/ ,size_t) ; 
 struct kvm_vcpu_hv* vcpu_to_hv_vcpu (struct kvm_vcpu*) ; 
 struct kvm_vcpu_hv_synic* vcpu_to_synic (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_hv_notify_acked_sint(struct kvm_vcpu *vcpu, u32 sint)
{
	struct kvm *kvm = vcpu->kvm;
	struct kvm_vcpu_hv_synic *synic = vcpu_to_synic(vcpu);
	struct kvm_vcpu_hv *hv_vcpu = vcpu_to_hv_vcpu(vcpu);
	struct kvm_vcpu_hv_stimer *stimer;
	int gsi, idx, stimers_pending;

	trace_kvm_hv_notify_acked_sint(vcpu->vcpu_id, sint);

	if (synic->msg_page & HV_SYNIC_SIMP_ENABLE)
		synic_clear_sint_msg_pending(synic, sint);

	/* Try to deliver pending Hyper-V SynIC timers messages */
	stimers_pending = 0;
	for (idx = 0; idx < ARRAY_SIZE(hv_vcpu->stimer); idx++) {
		stimer = &hv_vcpu->stimer[idx];
		if (stimer->msg_pending &&
		    (stimer->config & HV_STIMER_ENABLE) &&
		    HV_STIMER_SINT(stimer->config) == sint) {
			set_bit(stimer->index,
				hv_vcpu->stimer_pending_bitmap);
			stimers_pending++;
		}
	}
	if (stimers_pending)
		kvm_make_request(KVM_REQ_HV_STIMER, vcpu);

	idx = srcu_read_lock(&kvm->irq_srcu);
	gsi = atomic_read(&synic->sint_to_gsi[sint]);
	if (gsi != -1)
		kvm_notify_acked_gsi(kvm, gsi);
	srcu_read_unlock(&kvm->irq_srcu, idx);
}