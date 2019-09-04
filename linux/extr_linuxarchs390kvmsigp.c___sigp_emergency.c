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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int __inject_sigp_emergency (struct kvm_vcpu*,struct kvm_vcpu*) ; 

__attribute__((used)) static int __sigp_emergency(struct kvm_vcpu *vcpu, struct kvm_vcpu *dst_vcpu)
{
	return __inject_sigp_emergency(vcpu, dst_vcpu);
}