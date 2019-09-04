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
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;
struct kvm_s390_irq {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KVM_S390_SIGP_STOP ; 
 int SIGP_CC_BUSY ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int /*<<< orphan*/ ) ; 
 int kvm_s390_inject_vcpu (struct kvm_vcpu*,struct kvm_s390_irq*) ; 

__attribute__((used)) static int __sigp_stop(struct kvm_vcpu *vcpu, struct kvm_vcpu *dst_vcpu)
{
	struct kvm_s390_irq irq = {
		.type = KVM_S390_SIGP_STOP,
	};
	int rc;

	rc = kvm_s390_inject_vcpu(dst_vcpu, &irq);
	if (rc == -EBUSY)
		rc = SIGP_CC_BUSY;
	else if (rc == 0)
		VCPU_EVENT(vcpu, 4, "sent sigp stop to cpu %x",
			   dst_vcpu->vcpu_id);

	return rc;
}