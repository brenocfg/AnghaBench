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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {TYPE_3__* kvm; } ;
struct TYPE_5__ {TYPE_1__* kvm_ops; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_msr ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvmppc_set_msr(struct kvm_vcpu *vcpu, u64 msr)
{
	vcpu->kvm->arch.kvm_ops->set_msr(vcpu, msr);
}