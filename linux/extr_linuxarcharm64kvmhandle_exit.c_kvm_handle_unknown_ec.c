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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  esr_get_class_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_undefined (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_pr_unimpl (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_get_hsr (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_handle_unknown_ec(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	u32 hsr = kvm_vcpu_get_hsr(vcpu);

	kvm_pr_unimpl("Unknown exception class: hsr: %#08x -- %s\n",
		      hsr, esr_get_class_string(hsr));

	kvm_inject_undefined(vcpu);
	return 1;
}