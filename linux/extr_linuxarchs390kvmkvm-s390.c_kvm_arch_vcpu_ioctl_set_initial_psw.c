#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {TYPE_1__* run; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  mask; } ;
typedef  TYPE_2__ psw_t ;
struct TYPE_4__ {int /*<<< orphan*/  psw_addr; int /*<<< orphan*/  psw_mask; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  is_vcpu_stopped (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_arch_vcpu_ioctl_set_initial_psw(struct kvm_vcpu *vcpu, psw_t psw)
{
	int rc = 0;

	if (!is_vcpu_stopped(vcpu))
		rc = -EBUSY;
	else {
		vcpu->run->psw_mask = psw.mask;
		vcpu->run->psw_addr = psw.addr;
	}
	return rc;
}