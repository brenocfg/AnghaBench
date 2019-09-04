#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int skey_enabled; TYPE_3__* sie_block; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_2__* kvm; } ;
struct TYPE_7__ {int ictl; } ;
struct TYPE_5__ {int /*<<< orphan*/  use_skf; } ;
struct TYPE_6__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_KSS ; 
 int ICTL_ISKE ; 
 int ICTL_RRBE ; 
 int ICTL_SSKE ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int) ; 
 int /*<<< orphan*/  kvm_s390_clear_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_s390_test_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int s390_enable_skey () ; 
 int /*<<< orphan*/  trace_kvm_s390_skey_related_inst (struct kvm_vcpu*) ; 

int kvm_s390_skey_check_enable(struct kvm_vcpu *vcpu)
{
	int rc;

	trace_kvm_s390_skey_related_inst(vcpu);
	/* Already enabled? */
	if (vcpu->arch.skey_enabled)
		return 0;

	rc = s390_enable_skey();
	VCPU_EVENT(vcpu, 3, "enabling storage keys for guest: %d", rc);
	if (rc)
		return rc;

	if (kvm_s390_test_cpuflags(vcpu, CPUSTAT_KSS))
		kvm_s390_clear_cpuflags(vcpu, CPUSTAT_KSS);
	if (!vcpu->kvm->arch.use_skf)
		vcpu->arch.sie_block->ictl |= ICTL_ISKE | ICTL_SSKE | ICTL_RRBE;
	else
		vcpu->arch.sie_block->ictl &= ~(ICTL_ISKE | ICTL_SSKE | ICTL_RRBE);
	vcpu->arch.skey_enabled = true;
	return 0;
}