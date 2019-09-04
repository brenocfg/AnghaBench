#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* get_cpl ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 scalar_t__ __kvm_set_xcr (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_gp (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 

int kvm_set_xcr(struct kvm_vcpu *vcpu, u32 index, u64 xcr)
{
	if (kvm_x86_ops->get_cpl(vcpu) != 0 ||
	    __kvm_set_xcr(vcpu, index, xcr)) {
		kvm_inject_gp(vcpu, 0);
		return 1;
	}
	return 0;
}