#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int lctl; int ictl; } ;

/* Variables and functions */
 int CPUSTAT_EXT_INT ; 
 int CPUSTAT_IO_INT ; 
 int CPUSTAT_STOP_INT ; 
 int ICTL_LPSW ; 
 int ICTL_PINT ; 
 int ICTL_STCTL ; 
 int LCTL_CR0 ; 
 int LCTL_CR10 ; 
 int LCTL_CR11 ; 
 int LCTL_CR9 ; 
 scalar_t__ guestdbg_enabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_clear_cpuflags (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void __reset_intercept_indicators(struct kvm_vcpu *vcpu)
{
	kvm_s390_clear_cpuflags(vcpu, CPUSTAT_IO_INT | CPUSTAT_EXT_INT |
				      CPUSTAT_STOP_INT);
	vcpu->arch.sie_block->lctl = 0x0000;
	vcpu->arch.sie_block->ictl &= ~(ICTL_LPSW | ICTL_STCTL | ICTL_PINT);

	if (guestdbg_enabled(vcpu)) {
		vcpu->arch.sie_block->lctl |= (LCTL_CR0 | LCTL_CR9 |
					       LCTL_CR10 | LCTL_CR11);
		vcpu->arch.sie_block->ictl |= (ICTL_STCTL | ICTL_PINT);
	}
}