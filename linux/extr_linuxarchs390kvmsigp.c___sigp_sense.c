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
typedef  int u64 ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_STOPPED ; 
 int SIGP_CC_ORDER_CODE_ACCEPTED ; 
 int SIGP_CC_STATUS_STORED ; 
 int SIGP_STATUS_EXT_CALL_PENDING ; 
 int SIGP_STATUS_STOPPED ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int /*<<< orphan*/ ,int) ; 
 int kvm_s390_ext_call_pending (struct kvm_vcpu*) ; 
 int kvm_s390_test_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __sigp_sense(struct kvm_vcpu *vcpu, struct kvm_vcpu *dst_vcpu,
			u64 *reg)
{
	const bool stopped = kvm_s390_test_cpuflags(dst_vcpu, CPUSTAT_STOPPED);
	int rc;
	int ext_call_pending;

	ext_call_pending = kvm_s390_ext_call_pending(dst_vcpu);
	if (!stopped && !ext_call_pending)
		rc = SIGP_CC_ORDER_CODE_ACCEPTED;
	else {
		*reg &= 0xffffffff00000000UL;
		if (ext_call_pending)
			*reg |= SIGP_STATUS_EXT_CALL_PENDING;
		if (stopped)
			*reg |= SIGP_STATUS_STOPPED;
		rc = SIGP_CC_STATUS_STORED;
	}

	VCPU_EVENT(vcpu, 4, "sensed status of cpu %x rc %x", dst_vcpu->vcpu_id,
		   rc);
	return rc;
}