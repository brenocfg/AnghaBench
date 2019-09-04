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
 scalar_t__ kvm_vcpu_has_events (struct kvm_vcpu*) ; 
 scalar_t__ kvm_vcpu_running (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_runnable(struct kvm_vcpu *vcpu)
{
	return kvm_vcpu_running(vcpu) || kvm_vcpu_has_events(vcpu);
}