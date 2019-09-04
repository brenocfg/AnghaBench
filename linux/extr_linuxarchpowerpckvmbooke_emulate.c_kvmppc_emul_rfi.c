#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nip; } ;
struct TYPE_6__ {TYPE_2__* shared; TYPE_1__ regs; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/  srr1; int /*<<< orphan*/  srr0; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_set_msr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_emul_rfi(struct kvm_vcpu *vcpu)
{
	vcpu->arch.regs.nip = vcpu->arch.shared->srr0;
	kvmppc_set_msr(vcpu, vcpu->arch.shared->srr1);
}