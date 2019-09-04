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
typedef  size_t u8 ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  exit_handle_fn ;

/* Variables and functions */
 int /*<<< orphan*/ * arm_exit_handlers ; 
 size_t kvm_vcpu_trap_get_class (struct kvm_vcpu*) ; 

__attribute__((used)) static exit_handle_fn kvm_get_exit_handler(struct kvm_vcpu *vcpu)
{
	u8 hsr_ec = kvm_vcpu_trap_get_class(vcpu);

	return arm_exit_handlers[hsr_ec];
}