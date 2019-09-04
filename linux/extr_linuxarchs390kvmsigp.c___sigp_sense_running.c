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
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_RUNNING ; 
 int SIGP_CC_ORDER_CODE_ACCEPTED ; 
 int SIGP_CC_STATUS_STORED ; 
 int SIGP_STATUS_INVALID_ORDER ; 
 int SIGP_STATUS_NOT_RUNNING ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kvm_s390_test_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_kvm_facility (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __sigp_sense_running(struct kvm_vcpu *vcpu,
				struct kvm_vcpu *dst_vcpu, u64 *reg)
{
	int rc;

	if (!test_kvm_facility(vcpu->kvm, 9)) {
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_INVALID_ORDER;
		return SIGP_CC_STATUS_STORED;
	}

	if (kvm_s390_test_cpuflags(dst_vcpu, CPUSTAT_RUNNING)) {
		/* running */
		rc = SIGP_CC_ORDER_CODE_ACCEPTED;
	} else {
		/* not running */
		*reg &= 0xffffffff00000000UL;
		*reg |= SIGP_STATUS_NOT_RUNNING;
		rc = SIGP_CC_STATUS_STORED;
	}

	VCPU_EVENT(vcpu, 4, "sensed running status of cpu %x rc %x",
		   dst_vcpu->vcpu_id, rc);

	return rc;
}