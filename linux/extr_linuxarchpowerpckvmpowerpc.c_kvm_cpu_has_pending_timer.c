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
 int kvmppc_core_pending_dec (struct kvm_vcpu*) ; 

int kvm_cpu_has_pending_timer(struct kvm_vcpu *vcpu)
{
	return kvmppc_core_pending_dec(vcpu);
}