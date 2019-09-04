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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pmu_ops; } ;
struct TYPE_3__ {int (* is_valid_msr ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

bool kvm_pmu_is_valid_msr(struct kvm_vcpu *vcpu, u32 msr)
{
	return kvm_x86_ops->pmu_ops->is_valid_msr(vcpu, msr);
}